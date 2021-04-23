#include <ESP8266WiFi.h>

const char *ssid     = "test";          //wifi的ssid
const char *password = "12345678";      //wifi密码

const char *host = "api.heclouds.com"; //若无DNS，使用Server服务端的IP 183.230.40.33
const int httpPort = 6002;                 //Server服务端的端口号


void setup(void)
{
  Serial.begin(115200);
  Serial.println();       //换行
  Serial.printf("Wifi Connecting to %s\n", ssid);

  WiFi.mode(WIFI_STA);                         //默认情况下，ESP8266将尝试充当客户端和接入点。为避免干扰现有WIFI网络，明确将其设置为WiFi客户端。
  WiFi.begin(ssid, password);                  //启动Wifi连接

  while (WiFi.status() != WL_CONNECTED)        //阻塞式等待，直到连接成功
  {
    delay(500);                                 //每500MS检测一次，一直到连接成功
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi Connected OK, IP address: ");  //显示WIFI连接成功获取的本地IP
  Serial.println(WiFi.localIP());
}


//WiFiClient创建一个TCP客户端，可以连接到client.connect（）中定义的指定Internet IP地址服务器的端口。
//用HTTP协议连接OneNET服务器，并用POST方法上报数据
void loop()                                 
{
//用HTTP协议连接OneNET服务器
   WiFiClient client;                            //用WiFiClient类创建 client 对象，实现HTTP协议连接OneNET服务器
  if (!client.connect(host, port)) {       //若连接中移动服务器失败就等5秒，重新连接
    Serial.println("connection failed");
    delay(5000);                       //等5秒
    return;                                //程序返回到loop重新开始
  }
  
if (client.connected()) {              //若连接成功，就发送POST 请求上报数据
    String url = "http://api.heclouds.com/devices/674965073/datapoints?type=3";  //参数type=3表示用 简洁数据格式,5007777是你在移动OneNET上创建的设备ID
    client.print(String("PUT ")+url+" HTTP/1.1\r\n");                                                 //使用HTTP/1.1协议
    client.print(String("api-key: ")+"48UVqDcDe=vrqK=eOHV9LEKXEQ0=\r\n");             //需改为自己的主密钥
    client.print(String("Host: ")+"api.heclouds.com\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Length:23\r\n\r\n");

    client.print(String("{\"temperature\":"));
    client.print(12);                                       
    client.print(String(",\"humidity\":"));
    client.print(30);                                        
    client.print(String("}"));

  }
  client.stop();                     //关闭HTTP客户端
  delay(20000);

}
