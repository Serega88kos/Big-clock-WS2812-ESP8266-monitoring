//////////// НАСТРОЙКИ ////////////
#define Version_Firmware "2_beta_19"  // версия прошивки
//   питание платы от БП не выше 5В
//   DS3231        SDA=>D2 SCL=>D1 питание с 5В БП или с 3.3В
//   BMP/BME 280   SDA=>D2 SCL=>D1 питание 3.3В
//   DS18B20 питание 5В, если уличный без модуля ставим резистор между питанием и сигнальным на 4.7К

#define ONE_SENSORS_DS D5  // PIN датчика ds18b20
#define LEDS_IN_SEGMENT 4  // задаём сколько у нас светодиодов в сегменте
#define DOTS_NUM 2         // задаём сколько у нас разделительных точек 2/4/6/8
#define DOT_TEMP 0         // включаем точку десятых для температуры, 0 или 1
#define NUM_COLORS 16      // количество цветов, записаны в ColorTable, если хотите добавить/удалить, поправьте в коде:)
#define COLOR_ORDER GRB    // тип ленты, поменять порядок GRB на свой тип, если неправильные цвета
#define LED_PIN 6          // PIN дата от ленты, подключать через резистор 330Ом
#define milliamp 1000      // ограничение по току в мА

#define MP3_RX_PIN 2               //GPIO2/D4 к DFPlayer Mini TX
#define MP3_TX_PIN 16              //GPIO16/D0 к DFPlayer Mini RX
#define MP3_SERIAL_SPEED 9600      //DFPlayer Mini поддерживает только 9600 бод
#define MP3_SERIAL_BUFFER_SIZE 32  //размер последовательного буфера программного обеспечения в байтах, для отправки 8 байтов вам нужен 11-байтовый буфер (стартовый байт + 8 битов данных + байт четности + стоп-байт = 11 байтов)
#define MP3_SERIAL_TIMEOUT 350     //среднее время ожидания ответа DFPlayer для чипа GD3200B 350 мс..400 мс

//Настройки для DFPlayer
#define MP3_RX_PIN 2               //GPIO2/D4 к DFPlayer Mini TX
#define MP3_TX_PIN 16              //GPIO16/D0 к DFPlayer Mini RX
#define MP3_SERIAL_SPEED 9600      //DFPlayer Mini поддерживает только 9600 бод
#define MP3_SERIAL_BUFFER_SIZE 32  //размер последовательного буфера программного обеспечения в байтах, для отправки 8 байтов вам нужен 11-байтовый буфер (стартовый байт + 8 битов данных + байт четности + стоп-байт = 11 байтов)
#define MP3_SERIAL_TIMEOUT 350     //среднее время ожидания ответа DFPlayer для чипа GD3200B 350 мс..400 мс

//   если в схеме один фоторезистор не модулем, то вешаем резистор от 1К до 10К. Если у вас высокая освещенность, то 1К, если слабая, то до 10К
//   один вывод фоторезистора на пин A0, или любой другой, второй на GND. Между GND и питанием ставим резистор
#define BRI_PIN A0  // PIN фоторезистора

//Настройки OTA
#define GP_OTA_LIGHT
#define ota_name "admin"
#define ota_pass "pass"
#define web_start "clock"  //Адрес портала http://clock.local/ или по IP адресу, выданному роутером
#define portalTheme GP_LIGHT // GP_LIGHT, GP_DARK
#define colorTheme GP_BLUE   // GP_RED, GP_PINK, GP_VIOL, GP_BLUE, GP_CYAN, GP_GREEN,
                             // GP_YELLOW, GP_ORANGE, GP_GRAY, GP_BLACK, GP_WHITE

//Настройки точки доступа, IP 192.168.4.1
#define ssidAP "Clock_ESP"
#define passAP "administrator"  // не менее 8 символов

struct Wifi {
  char ssid[32] = "";
  char pass[32] = "";
};
Wifi w;

struct Clock {
  int gmt = 3;                                        // часовой пояс, 3 для МСК
  char host[32] = "pool.ntp.org";                     // NTP сервер
  bool rtc_check = 1;                                 // 1 - есть модуль RTC, 0 - нет
  uint8_t change_color = 0;                           // смена цвета ( 0 - никогда, 1 - раз в минуту, 2 - каждые десять минут, 3 - каждый час, 4 - каждые десять часов)
  bool prs = 0;                                       // 0 - не показываем символ давления, 1 - показать
  bool hmd = 1;                                       // 0 - не показываем символ влажности, 1 - показать
  bool symbol = 0;                                    // 0 - не показывать первый ноль в часах, 1 - показать
  bool type_sec = 1;                                  // режим мигания секунд, 0 - 1р/с, 1 - 2р/с
                                                      // режимы часов
                                                      // 0 - часы, 1 - комнатная температура, 2 - уличная температура, 3 - давление, 4 - влажность, 5 - дата !!255 - обязательный последний маркер!!
  uint8_t periodDisplay[7] = { 6, 2, 2, 2, 2, 255 };  //сколько по времени выводить каждый режим, сек
  uint8_t orderDisplay[7] = { 0, 1, 2, 3, 4, 255 };   //порядок вывода режимов
  bool new_god = 0;                                   // включить гирлянду на Новый Год :)
};
Clock c;

struct Other {
  float cor_tempH = 0;             // корректировка показаний датчика комнатной температуры
  float cor_tempS = 0;             // корректировка показаний датчика уличной температуры
  int8_t cor_pres = 0;             // корректировка показаний датчика давления
  int8_t cor_hum = 0;              // корректировка показаний датчика влажности
  bool type_brg = 0;               // выбрать тип датчика, 0 - аналог, 1 - цифровой
  bool auto_bright = 1;            // автоматическая подстройка яркости от уровня внешнего освещения (1 - включить, 0 - выключить)
  uint8_t min_bright = 10;         // минимальная яркость (0 - 255)
  uint8_t max_bright = 200;        // максимальная яркость (0 - 255)
  uint8_t brg = 10;                // как часто проверять изменение по датчику освещенности в сек
  uint16_t bright_constant = 700;  // константа усиления от внешнего света (0 - 1023), чем МЕНЬШЕ константа, тем "резче" будет прибавляться яркость
  float coef = 0.4;                // коэффициент фильтра (0.0 - 1.0), чем больше - тем медленнее меняется яркость
};
Other o;

//   при отправке больше одного запроса в 5 минут, получите бан по IP, либо получите повышенные привелегии за помощь проекту, тогда ограничения изменяются :)
//   регистрирумся на narodmon.ru, загружаем настроенный скетч, в меню профиль, отладка по IP копируем Mac
//   снова профиль, мои датчики, вводим Mac и настраиваем датчики по усмотрению и радуемся их работе :)
struct Monitoring {
  bool Monitoring = false;      // включаем мониторинг, иначе false
  uint16_t delay_narod = 310;  // как часто отправлять значения датчиков на мониторинг, минимум 5 минут, значение в секундах, плюс запас в 5 сек, на всякий случай, получается минимум 305
  bool nm_tempH = true;        // включить отправку показаний комнатной температуры
  bool nm_tempS = true;        // включить отправку показаний уличной температуры
  bool nm_pres = true;         // включить отправку показаний давления
  bool nm_hum = true;          // включить отправку показаний влажности
};
Monitoring m;

struct DFP {
  bool status_kuku = false;     // включаем модуль DFP
  uint8_t start_kuku = 0;       // время работы в часах, начало
  uint8_t stop_kuku = 0;        // время работы в часах, окончание
  bool kuku_mp3_check = false;  // режим кукушка
  bool vrem_mp3_check = false;  // режим оповещения времени
  uint8_t grom_mp3 = 0;         // громкость 0-30
  uint8_t golos = 0;            // голосовой пакет
};
DFP r;

/////////////////// КОНЕЦ НАСТРОЕК /////////////////
