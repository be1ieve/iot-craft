IOT Craft 使用說明

程式內容見[github](https://github.com/be1ieve/iot-craft)
# 用途簡介
* 不固定數量的手持設備，每個設備有獨立的編號，且可顯示少量的內容
* 不定數量但位置相對已知的桌面設備，每個桌面設備都有各自不定數量的感應點。
* 透過將手持設備接觸某個桌面設備的某個感應點，我們將可描繪其活動軌跡。
* 有個雲端設備負責綁定手持設備到特定人物，之後透過監聽設備互動訊息可紀錄出個人的獨特軌跡或提供獨特內容給相對應設備。

# 硬體設備
## 手持設備
* Raspberry Pi Pico W： 作為主模塊使用，且開啟BLE連線功能。
* waveshare 1.54吋電子紙模塊： 作為目前預設的內容顯示方式。
* 磁鐵： 作為與桌面設備感應點的感應方式。
* 3.7v鋰電池： 設備可移動攜帶，故需另附電池獨立供電。
## 桌面設備
* Raspberry Pi Pico W： 作為主模塊使用，且開啟BLE與WiFi連線功能。
* 磁簧感應開關： 作為手持設備靠近的感應方式，在各個感應點皆須佈置。
* 直接透過PICO W的USB供電，因為須與雲端設備保持連接故電源也需要保持連接。
## 雲端設備
* 設備不限制，但至少要具有網路連線功能連接獨立MQTT broker。
  或設備內含MQTT broker，並能以網路方式與桌面設備溝通。

# 軟體環境
## 手持設備
* 系統採用Arduino與第三方函式庫編寫而成。
  Arduino底層為：[arduino-pico](https://github.com/earlephilhower/arduino-pico)
  於Arduino程式中以函式庫的方式引入且不加修改：[ArduinoJSON](https://github.com/bblanchon/ArduinoJson)
  附於原始檔中存在並有修改內容的函式庫：[epd1in54_V2](https://github.com/waveshareteam/e-Paper/tree/master/Arduino/epd1in54_V2)
* 原始檔中的config.h為主要須修改內容，編譯前須確認。
## 桌面設備
* 系統採用Arduino與第三方函式庫編寫而成。
  Arduino底層為：[arduino-pico](https://github.com/earlephilhower/arduino-pico)
  於Arduino程式中以函式庫的方式引入且不加修改：
  [ArduinoJSON](https://github.com/bblanchon/ArduinoJson)，[PubSubClient](https://github.com/knolleary/pubsubclient)，[RPI_PICO_TimerInterrupt](https://github.com/khoih-prog/RPI_PICO_TimerInterrupt)
* 原始檔中的config.h為主要須修改內容，編譯前須確認。
## 雲端設備
* 雲端設備須提供MQTT broker功能，或另提供公開的broker並監聽對應的項目。
  * 每個設備皆佔有一個獨立的輸入項目，作為從雲端對手持設備下指令的通道。
  * 每個桌面設備佔有一個獨立的輸出項目，當有手持設備連接時透過此項目通知雲端設備。
* 手持設備與桌面設備本身不記憶所有交互過程與內容，皆交由雲端設備處理。
  雲端設備不限制用任何方式紀錄，僅最後會以JSON格式包裝並傳送對應指令給對應的設備。

# 設定方式
## 手持設備
* config.h
  ``` c
  #define NAME_PREFIX "IOT-"
  char DEVICE_NAME[20] = "CUSTOM_NAME_HERE";
  ```
  NAME_PREFIX為整個專案所用的名稱前綴，所有設備須保持一致。
  DEVICE_NAME為設備的名稱，若不是以前綴開始則會自動以mac address取代。
* epaper模塊預設的腳位與原先的不同，所以需要在下面兩個檔案中重新定義。
  * epdif.h
    ``` c
    // Pin definition
    #define RST_PIN         7
    #define DC_PIN          6
    #define CS_PIN          5
    #define BUSY_PIN        8
    #define SCK_PIN         2
    #define MOSI_PIN        3
    #define MISO_PIN        4
    ```
  * epdif.cpp
    ``` c
    int EpdIf::IfInit(void) {
        pinMode(CS_PIN, OUTPUT);
        pinMode(RST_PIN, OUTPUT);
        pinMode(DC_PIN, OUTPUT);
        pinMode(BUSY_PIN, INPUT);
        SPI.setRX(MISO_PIN);
        SPI.setTX(MOSI_PIN);
        SPI.setCS(CS_PIN);
        SPI.setSCK(SCK_PIN);
        SPI.begin();
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
        return 0;
    }
    ```
## 桌面設備
* config.h
  ``` c
  #define NAME_PREFIX "IOT-"
  char DEVICE_NAME[20] = "CUSTOM_NAME_HERE";
  
  #define WIFI_SSID "SSID"
  #define WIFI_PASSWORD "PASSWORD"
  
  #define MQTT_SERVER "mqtt-dashboard.com"
  #define MQTT_PREFIX "iot-craft/"
  #define MQTT_TOPIC_OUTPUT "/output"
  #define MQTT_TOPIC_INPUT "/input"
  #define MQTT_UPDATE_INTERVAL_US 5000000

  sensor_pin_t SENSOR_PINS[]={{20,"Left"},{21,"Middle"},{22,"Right"}};
  ```
  NAME_PREFIX為整個專案所用的名稱前綴，所有設備須保持一致。
  DEVICE_NAME為設備的名稱，若不是以前綴開始則會自動以mac address取代。
  WIFI_SSID與WIFI_PASSWORD為WIFI的連線使用，注意PICO W的可用距離可能比手機還短。
  MQTT_SERVER為MQTT主機的位置，不一定就是雲端設備，只要皆連到同一個MQTT主機即可。
  MQTT_PREFIX、MQTT_TOPIC_OUTPUT、MQTT_TOPIC_INPUT為構成輸出入項目的主體，注意用於MQTT分層的"/"符號須保留。
  MQTT_UPDATE_INTERVAL_US為設備與主機通訊的間隔時間，太短可能會被主機屏蔽，太長影響指令接收的反應。
## 雲端設備
* MQTT設定依照不同軟體自行設定。依據桌面設備的MQTT_PREFIX、MQTT_TOPIC_OUTPUT、MQTT_TOPIC_INPUT加上各設備的DEVICE_NAME拼湊

# 操作過程
## 手持設備
* 手持設備第一次開機顯示待機畫面，同時開始BLE廣播
* 手持設備在接受桌面設備的連接後，顯示畫面會清除並顯示另一個背景，並等待更新畫面。
  在連線維持的狀態下顯示畫面不會清除，只會一直覆蓋新的內容。
  連線中斷後畫面仍會維持，但下次再連線時會清除回到僅背景的狀態。
* 手持設備透過BLE可以接收JSON格式的指令並執行對應的動作
## 桌面設備
* 桌面設備開機後自動連網，並與MQTT主機建立連接。
  連接過程中會一直監聽屬於自己的輸入項目，若有相對應的JSON指令傳輸過來會解讀並反應，
* 當手持設備碰觸到感應點時，會主動以BLE連接最接近的設備。
  與手持設備相連後，會取得手持設備對應的資料，並與感應點名稱一起打包傳到雲端設備。
* 手持設備連接期間，桌面設備亦會同時監聽屬於該設備的輸入項目，若有指令傳輸則直接以BLE轉送不對其內容解析。
## 無線路由器
* 桌面設備透過WiFi與外界溝通，故須於桌面設備可連線範圍內提供無線網路服務。
* PICO W目前僅支援2.4GHz網路，且須以WPA Personal的方式連線。
  亦即須要能使用指定SSID與密碼的方式連線，不支援無密碼登入再網頁認證的方式連線。
* 透過提供的無線網路，桌面設備需要可以連接到指定的MQTT broker。
## 雲端設備
* 雲端設備須提供或有指定MQTT broker，隨時監聽所有此專案的訊息。
* 當收到桌面設備的訊息，可從中取得桌面設備的ID與觸發的點，同時亦可取得手持設備ID。
  透過手持設備ID就可拼湊出手持設備的輸入項目，往該處的訊息將直接轉發給手持設備。
* 雲端設備紀錄設備連接時程，並可依據其他綁定資訊獨立判斷。
  運算完的內容再透過MQTT的方式傳送到指定的設備，若有多個設備亦須個別傳送。

# 遠端指令
* 桌面設備因與MQTT主機會維持連接，故可於任意時間狀態與雲端設備溝通。
* 手持設備僅在與桌面設備連接的期間可透過桌面設備向雲端設備收發訊息。
* 指令傳輸前要包裝為JSON格式，不論是透過BLE或是MQTT
## 指令增減方式
* 新增指令時要注意內容不可與已有的指令衝突，但若是已定義未引用的就無關。
* 輸入指令的程式內容以獨立.h檔包裝，在主程式最前端引入。指令的判讀則接續在主程式的deserializeJson()之後，可參考image.h與poker.h的做法。
  ``` c=111
  deserializeJson(doc, tempStr);

  #ifdef _XXXX_H_
    //指令判讀內容
    ...
  #endif
  ```
## 桌面設備輸出
* 項目位置為： <MQTT_PREFIX>/<DEVICE_NAME>/<MQTT_TOPIC_OUTPUT>
  以目前預設範例來看就是： iot-craft/IOT-XXXXXX/output
* JSON格式訊息內容如下：
  ``` json
  {
      "name":"桌面設備名稱",
      "pin":"觸發點名稱",
      "handheld":"手持設備名稱",
      "battery":"手持設備電量",
      "value":"手持設備資訊"
  }
  ```
  注意目前電量與設備資訊未實作，僅以亂數隨機顯示
## 各式設備輸入
* 項目位置為： <MQTT_PREFIX>/<DEVICE_NAME>/<MQTT_TOPIC_INPUT>
  以目前預設範例來看就是： iot-craft/IOT-XXXXXX/input
* 設備輸入可直接修改arduino原始檔，在解析JSON後加入對應的功能。
* 注意目前透過BLE只能傳輸600Bytes的資料，過大的內容會直接被省略。
### 範例 image.h
* 電子紙無法直接使用一般的圖片，須先透過Image2LCD轉檔存為C矩陣型態。
* 因為能用BLE傳送的內容太小，所以只能預先定義在檔案中，後續再依據代號取用。
  現於範例檔中內建26個圖片定義，分別為IMAGE_A到IMAGE_Z，未使用到的內容皆填零。
* 每個圖片有三個變數： IMAGE_X_WIDTH，IMAGE_X_HEIGHT與IMAGE_X
  寬度WIDTH必須為8的倍數，否則無法顯示。高度HEIGHT沒有限制
  圖片內容矩陣大小會是寬度*高度/8的結果，直接從Image2LCD輸出的內容複製即可
* JSON格式指令內容如下：
  ``` json
  {
      "image":"<IMAGE_ID>",
      "x":"<CENTER_X>",
      "y":"<CENTER_Y>",
  }
  ```
* {"image":"C","x":"100","y":"120"} 會將IMAGE_C的圖貼在(100,120)的位置

### 範例 poker.h
* 範例檔中內建5個花色定義以及A 2 3 4 5 6 7 8 9 10 J Q K這些文字內容
* JSON格式指令內容如下：
  ``` json
  {
    "poker":"<SUIT><NUMBER>"
  }
  ```
* {"poker":"S08"} 會顯示黑桃8

