//	Библиотека для работы с датчиками температуры: «DS18S20», «DS18B20», «DS1822» https://iarduino.ru/shop/Sensory-Datchiki/сlimatic/
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_DS18XXX_h
#define iarduino_DS18XXX_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <OneWire.h>

#define	DS18S20		1
#define	DS18B20		2
#define	DS1822		3

class iarduino_DS18XXX{													//
	public:			iarduino_DS18XXX(uint8_t);							//
		uint8_t		get_Type(byte  );									//  Получить модель датчика температуры по первому байту адреса.
		bool		get_Addr(byte* );									//  Получить адрес устройства на шине OneWire.
		bool		get_Data(byte* );									//  Получить данные датчика температуры на шине OneWire.
		bool		get_Temp(float&);									//  Получить температуру в °С.
		float		get_Temp( void ){float i=0; get_Temp(i); return i;}	//  Получить температуру в °С.
	private:															//
		byte		a[8];												//	Объявляем массив для хранения адреса устройства на шине OneWire.
		byte		d[9];												//	Объявляем массив для получения данных по шине OneWire.
		void*		obj_Sensor;											//	Объявляем пустой указатель для работы с библиотекой OneWire.
};																		//

#endif