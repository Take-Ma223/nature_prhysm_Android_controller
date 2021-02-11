#pragma once
class Controller
{
public:
	Controller();
	~Controller();


	void load();
	void calc();
	void show();
	void run();

	void send_UDP(char *str);
	void Get_Key_State();
	void Get_IP();
private:
	int H_BG;
	int H_Button[4];
	int SH_ButtonSound[3];
	int SH_ButtonSound_s[3];

	int button_x = 0;//左上の座標
	int button_y = 0;
	int button_dist = 240;//配置距離
	int button_dist_x = 320;//x軸配置距離
	int button_offset = 40;//ボタンを中心に寄せるためのオフセット

	int edge = 50;//端領域

	int button_press[12];//ボタンの押下状態(0:離している 1:押している)
	int button_press_before[12];//前フレームのボタンの押下状態(0:離している 1:押している)


	int GAME_passed_time = 0;
	int GAME_start_time = 0;
	int LOOP_passed_time = 1;
	int time_cash = 0;

	char IP[32]="192.168.1.1";//送信先IPアドレス

	char Buf[256];
	int Key[256];

	JNIEnv *env;
	const ANativeActivity *NativeActivity;
	int InputEnd;
	char InputString[1024] = "";
	jclass jclass_nature_prhysm_controller;
	jmethodID jmethodID_send_UDP;

	FILE *fp;
	char FilePath[256];//IPアドレス保存ファイル



};

