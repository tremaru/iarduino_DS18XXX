#include "iarduino_DS18XXX.h"												//
																			//
//		Конструктор класса:													//
		iarduino_DS18XXX::iarduino_DS18XXX(uint8_t pin){					//	Функция принимает номер вывода к которому подключён датчик температуры.
			obj_Sensor = new OneWire(pin);									//	
		}																	//	
																			//
//		Функция получения адреса устройства на шине OneWire:				//
bool	iarduino_DS18XXX::get_Addr(byte* addr){								//	Функция принимает указатель на массив размером в 8 элементов типа byte.
		//	Сбрасываем предыдущий найденный адрес:							//
			(*(OneWire*)obj_Sensor).reset_search();							//	Без сброса функция продолжит искать следующий адрес после найденного в предыдущий раз.
		//	Ищем новый адрес устройства на шине OneWire:					//
			if( !(*(OneWire*)obj_Sensor).search(addr) ){ return false; }	//	Если адрес не найден, то функция вернёт false.
		//	Проверяем CRC8 адреса:											//
			if( OneWire::crc8(addr,7) != addr[7]      ){ return false; }	//	CRC8 первых 7 байт адреса должно совпасть со значением последнего байта адреса.
		//	Возвращаем положительный результат чтения адреса:				//
			return true;													//	
}																			//
																			//
//		Функция получения модели датчика температуры:						//
uint8_t	iarduino_DS18XXX::get_Type(byte addr){								//	Функция принимает первый байт адреса устройства.
			switch( addr ){													//
				case 0x10:	return DS18S20; break;							//
				case 0x28:	return DS18B20; break;							//
				case 0x22:	return DS1822;  break;							//
				default:	return 0;		break;							//
			}																//
}																			//
																			//
// 		Функция получения данных от датчика температуры:					//
bool	iarduino_DS18XXX::get_Data(byte* data){								//	Функция принимает указатель на массив размером в 9 элементов типа byte.
		//	Получаем адрес устройства:										//
			if( !get_Addr(a)    ){ return false; }							//
		//	Проверяем устройство на принадлежность к датчику температуры:	//
			if( !get_Type(a[0]) ){ return false; }							//
		//	Указываем датчику выполнить конвертацию температуры:			//
			(*(OneWire*)obj_Sensor).reset();								//	Отправляем сигнал сброса.
			(*(OneWire*)obj_Sensor).select(a);								//	Выбираем устройство указав его адрес.
			(*(OneWire*)obj_Sensor).write(0x44, 0);							//	Отправляем команду на выполнение конвертации температуры.
			delay(100);														//	Задержка.
		//	Читаем результат:												//
			(*(OneWire*)obj_Sensor).reset();								//	Отправляем сигнал сброса.
			(*(OneWire*)obj_Sensor).select(a);								//	Выбираем устройство указав его адрес.
			(*(OneWire*)obj_Sensor).write(0xBE);							//	Отправляем команду на вывод данных из scratchpad-памяти.
			for(uint8_t i=0; i<9; i++){										//
				data[i]=(*(OneWire*)obj_Sensor).read();						//	Читаем 9 байт данных.
			}																//
		//	Проверяем CRC8 данных:											//
			if( OneWire::crc8(data,8) != data[8] ){ return false; }			//	Проверка контрольной суммы (CRC8 для первых 8 байт данных должно совпасть со значением последнего байта данных).
		//	Возвращаем положительный результат чтения данных:				//
			return true;													//	
}																			//
																			//
// 		Функция получения температуры в °С:									//
bool	iarduino_DS18XXX::get_Temp(float& temp){							//	Функция принимает ссылку на переменную для получения температуры.
		//	Получаем данные от датчика температуры:							//
			if( !get_Data(d) ){ return false; }								//
			int16_t t = (d[1]<<8) | d[0];									// Значение температуры хранятся в двух первых байтах данных.
		//	Определяем разрешение используемое датчиком:					//
			if( get_Type(a[0])==DS18S20 ){									// Если устройство является датчиком температуры DS18S20, то
				t <<= 3;													// Сдвигаем значение на 3 бита влево, так как у датчика 12-битное разрешение.
				if(d[7]==0x10){t=(t&0xFFF0)+12-d[6];}						// Если установлен старший бит 8 байта данных, то пересчитываем полученное значение.
			}else{															//
				switch( d[4]&0x60 ){										// Определяем разрешение по двум битам 5 байта данных.
					case 0x00: t &= ~7; break;								// Датчик температуры использует  9-битное разрешение.
					case 0x20: t &= ~3; break;								// Датчик температуры использует 10-битное разрешение.
					case 0x40: t &= ~1; break;								// Датчик температуры использует 11-битное разрешение.
				}															// Датчик температуры использует 12-битное разрешение.
			}																//
			temp = (float)t/16.0f;											// Переводим значение в °С.
		//	Возвращаем положительный результат чтения данных:				//
			return true;													//	
}																			//
