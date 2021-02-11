#include"DxLib.h"
#include "Controller.h"
#include<string.h>


Controller::Controller()
{
	for (int i = 0; i <= 11; i++) {//押下情報初期化
		button_press[i] = 0;
		button_press_before[i] = 0;
	}


	GetInternalDataPath(FilePath, sizeof(FilePath));
	strcat(FilePath, "/SaveFile.bin");

	fp = fopen(FilePath, "r");
	if (fp != NULL) {
		fgets(IP,64,fp);
		fclose(fp);
	}

}


Controller::~Controller()
{
}

void Controller::load() {
	H_Button[0] = LoadGraph("button_BB.png");
	H_Button[1] = LoadGraph("button_GB.png");
	H_Button[2] = LoadGraph("button_RB.png");
	H_Button[3] = LoadGraph("button_pressB.png");
	H_BG = LoadGraph("bg.png");

	SH_ButtonSound[0] = LoadSoundMem("hit_b_n.wav",2);
	SH_ButtonSound[1] = LoadSoundMem("hit_g_n.wav",2);
	SH_ButtonSound[2] = LoadSoundMem("hit_r_n.wav",2);
	SH_ButtonSound_s[0] = LoadSoundMem("hit_b_s.wav",2);
	SH_ButtonSound_s[1] = LoadSoundMem("hit_g_s.wav",2);
	SH_ButtonSound_s[2] = LoadSoundMem("hit_r_s.wav",2);

}

void Controller::calc() {
	GAME_passed_time = GetNowCount() - GAME_start_time;//経過時間計算
	LOOP_passed_time = GAME_passed_time - time_cash;//1ループにかかった時間を算出
	time_cash = GAME_passed_time;

	int InputNum = 0;
	InputNum = GetTouchInputNum();

	if (InputNum >= 13) {
		InputNum = 12;
	}

	for (int i = 0; i <= 11; i++) {
		button_press[i] = 0;
	}

	int x = 0, y = 0;
	for (int i = 0; i <= InputNum-1; i++) {
		GetTouchInput(i,&x,&y,NULL,NULL);
		for (int j = 0; j <= 3; j++) {//横
			for (int k = 0; k <= 2; k++) {//縦
				if (button_x + j*button_dist_x <= x && button_x + j*button_dist_x + button_dist_x > x
					&& button_y + k*button_dist <= y && button_y + k*button_dist + button_dist > y) {//ボタンの範囲内を押しているか
					button_press[j + 4 * k] = 1;

					/*
					else if (j == 0 && button_x >= x
						&& button_y + k*button_dist <= y && button_y + k*button_dist + button_dist > y) {//端でも反応させる
						button_press[4 * k] = 1;
					}
					else if(j == 3 && button_x + j*button_dist + button_dist<= x
						&& button_y + k*button_dist <= y && button_y + k*button_dist + button_dist > y) {//端でも反応させる
						button_press[3 + 4 * k] = 1;
					}
					*/
					if (button_x + j*button_dist_x + edge <= x && button_x + j*button_dist_x + button_dist_x - edge > x
						&& button_y + k*button_dist + edge <= y && button_y + k*button_dist + button_dist - edge > y) {//しっかり真ん中を押していたら
					}
					else {
						//Vibrator_vibrate(120, 255);//振動させる
					}

					if (k == 1) {
						//Vibrator_vibrate(120, 255);//振動させる
					}


					if (button_press_before[j + 4 * k] == 0) {//前フレームで押してなかったので音を鳴らす
						if (button_x + j*button_dist_x + edge <= x && button_x + j*button_dist_x + button_dist_x - edge > x
							&& button_y + k*button_dist + edge <= y && button_y + k*button_dist + button_dist - edge > y) {//しっかり真ん中を叩けていたら
							PlaySoundMem(SH_ButtonSound[k], DX_PLAYTYPE_BACK, TRUE);
							//Vibrator_vibrate(60, 255);
						}
						else {//端っこを叩いた時
							PlaySoundMem(SH_ButtonSound_s[k], DX_PLAYTYPE_BACK, TRUE);
							

							//PlaySoundMem(SH_ButtonSound_s[k], DX_PLAYTYPE_BACK, TRUE);
						}

					}
				}
			}
		}
	}


	for (int j = 0; j <= 3; j++) {//横
		for (int k = 0; k <= 2; k++) {//縦
			if ((button_press[j + 4 * k] == 1) && (button_press_before[j + 4 * k] == 0)) {//前フレームで押されてなく今回押されたとき
				char send_str[4];
				if (k == 0) {//青
					sprintfDx(send_str, "B%d1", j);
				}
				if (k == 1) {//緑
					sprintfDx(send_str, "G%d1", j);
				}
				if (k == 2) {//赤
					sprintfDx(send_str, "R%d1", j);
				}
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
			}
			if ((button_press[j + 4 * k] == 0) && (button_press_before[j + 4 * k] == 1)) {//前フレームで押されてたが今回離されたとき
				char send_str[4];
				if (k == 0) {//青
					sprintfDx(send_str, "B%d0", j);
				}
				if (k == 1) {//緑
					sprintfDx(send_str, "G%d0", j);
				}
				if (k == 2) {//赤
					sprintfDx(send_str, "R%d0", j);
				}
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
				send_UDP(send_str);
			}
		}
	}



	for (int i = 0; i <= 11; i++) {//現在のフレームのキー押下情報を保存
		button_press_before[i] = button_press[i];
	}

	clsDx();
	printfDx("%d\n", InputNum);
	



}

void Controller::show() {
	ClearDrawScreen();

	DrawGraph(0, 0, H_BG, TRUE);//背景


	int i = 0;
	int j = 0;

	for (i = 0; i <= 2; i++) {
		for (j = 0; j <= 3; j++) {
			DrawGraph(button_x + button_dist_x*j + button_offset, button_y + button_dist*i, H_Button[i], TRUE);//ボタン
			if (button_press[j + 4 * i] == 1) {//そこのボタンが押されてたら
				DrawGraph(button_x + button_dist_x*j + button_offset, button_y + button_dist*i, H_Button[3], TRUE);//ボタン(押している)
			}
		}
	}
	//printfDx("IP_Str:%s\n", InputString);
	printfDx("IP:%s\n", IP);
	ScreenFlip();
}

void Controller::run() {
	load();
	GAME_start_time = GetNowCount();
	while (1) {
		if (ProcessMessage() != 0) {//ESCでゲーム終了
			DxLib_End();
			return;
		}
		Get_Key_State();
		if (Key[KEY_INPUT_ESCAPE] == 1) {
			Get_IP();//IPアドレスを入力
		}
		calc();
		show();

		//WaitTimer(1);
	}
}

void Controller::send_UDP(char *str) {
	JNIEnv *env;
	const ANativeActivity *NativeActivity;
	int InputEnd;
	char InputString[1024];
	// アプリの NativeActivity を取得しておく
	NativeActivity = GetNativeActivity();
	//printfDx("1\n");
	//ScreenFlip();
	// Java の関数 StartInputStringDialog の呼び出し
	{
		// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
		if (NativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK)
		{
			return;
		}
		//printfDx("2\n");
		//ScreenFlip();
		// Java のクラス nature_prhysm_controller を取得
		jclass jclass_nature_prhysm_controller = env->GetObjectClass(NativeActivity->clazz);

		// Java のクラス nature_prhysm_controller のメンバー関数 StartInputStringDialog の ID を取得
		//jmethodID jmethodID_StartInputDialog = env->GetMethodID(jclass_nature_prhysm_controller, "StartInputStringDialog", "()V");

		// Java のクラス nature_prhysm_controller のメンバー関数 StartInputStringDialog の呼び出し
		//env->CallVoidMethod(NativeActivity->clazz, jmethodID_StartInputDialog);

		//printfDx("3\n");
		//ScreenFlip();
		// Java のクラス nature_prhysm_controller のメンバー関数 send_UDP の ID を取得
		jmethodID jmethodID_send_UDP = env->GetMethodID(jclass_nature_prhysm_controller, "send_UDP", "(Ljava/lang/String;Ljava/lang/String;)V");

		//printfDx("4\n");
		//ScreenFlip();
		// Java のクラス nature_prhysm_controller のメンバー関数 send_UDP の呼び出し
		env->CallVoidMethod(NativeActivity->clazz, jmethodID_send_UDP, env->NewStringUTF(IP), env->NewStringUTF(str));


		//printfDx("5\n");
		//ScreenFlip();
		// Java のクラス nature_prhysm_controller の参照を削除
		env->DeleteLocalRef(jclass_nature_prhysm_controller);


		//printfDx("6\n");
		//ScreenFlip();
		// JavaVM とソフト実行用スレッドの関連付け終了
		NativeActivity->vm->DetachCurrentThread();

		//printfDx("7\n");
		//ScreenFlip();
	}


}

void Controller::Get_Key_State() {//Key[]にキーの押下状態を入れる
	int i;

	GetHitKeyStateAll(Buf);//Bufにキーの押下状態が入る(離していたら全て0)

	for (i = 0; i <= 255; i++) {
		if (Buf[i] == 0) {//今は押されていない
			if (Key[i] <= 0)Key[i] = 0;//離され続けてる
			if (Key[i] >  0)Key[i] = -1;//離された瞬間
		}
		else {//今は押されている
			Key[i]++;//
		}
	}

	return;
}

void Controller::Get_IP() {

	// アプリの NativeActivity を取得しておく
	NativeActivity = GetNativeActivity();

	// Java の関数 StartInputStringDialog の呼び出し
	{
		// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
		if (NativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK)
		{
			return;
		}

		// Java のクラス nature_prhysm_controller を取得
		jclass jclass_nature_prhysm_controller = env->GetObjectClass(NativeActivity->clazz);

		// Java のクラス nature_prhysm_controller のメンバー関数 StartInputStringDialog の ID を取得
		jmethodID jmethodID_StartInputDialog = env->GetMethodID(jclass_nature_prhysm_controller, "StartInputStringDialog", "()V");

		// Java のクラス nature_prhysm_controller のメンバー関数 StartInputStringDialog の呼び出し
		env->CallVoidMethod(NativeActivity->clazz, jmethodID_StartInputDialog);

		// Java のクラス nature_prhysm_controller の参照を削除
		env->DeleteLocalRef(jclass_nature_prhysm_controller);

		// JavaVM とソフト実行用スレッドの関連付け終了
		NativeActivity->vm->DetachCurrentThread();
	}

	// 入力が完了したかどうかのフラグを倒す
	InputEnd = 0;

	while (1) {
		if (ProcessMessage() != 0) {//ESCでゲーム終了
			DxLib_End();
			return;
		}

		// 入力が完了していなかったら Java のクラス nature_prhysm_controller のメンバー変数 InputEnd と InputString の情報を取得する
		if (InputEnd == 0)
		{
			// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
			if (NativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK)
			{
				return;
			}

			// Java のクラス nature_prhysm_controller を取得
			jclass jclass_nature_prhysm_controller = env->GetObjectClass(NativeActivity->clazz);

			// Java のクラス nature_prhysm_controller のメンバー変数 InputEnd の ID を取得
			jfieldID jfieldID_InputEnd = env->GetFieldID(jclass_nature_prhysm_controller, "InputEnd", "I");

			// Java のクラス nature_prhysm_controller のメンバー変数 InputEnd の値をローカル変数 InputEnd に代入
			InputEnd = env->GetIntField(NativeActivity->clazz, jfieldID_InputEnd);

			// InputEnd が 1 になっていたら入力が完了しているので InputString の値を取得する
			if (InputEnd == 1)
			{
				// Java のクラス nature_prhysm_controller のメンバー変数 InputString の ID を取得
				jfieldID jfieldID_InputString = env->GetFieldID(jclass_nature_prhysm_controller, "InputString", "Ljava/lang/String;");

				// Java のクラス nature_prhysm_controller のメンバー変数 InputString の jstring オブジェクトを取得
				jstring jstring_InputString = (jstring)env->GetObjectField(NativeActivity->clazz, jfieldID_InputString);

				// Java のクラス nature_prhysm_controller のメンバー変数 InputString の jstring から C++ 用の文字列のアドレスを取得
				const char *chars_InputString = env->GetStringUTFChars(jstring_InputString, NULL);

				// 文字列をローカル変数 InputString にコピー
				strcpy(InputString, chars_InputString);

				// Java のクラス nature_prhysm_controller のメンバー変数 InputString の jstring から取得した C++ 用の文字列のアドレスを解放
				env->ReleaseStringUTFChars(jstring_InputString, chars_InputString);

				// Java のクラス nature_prhysm_controller のメンバー変数 InputString の jstring オブジェクトの参照を削除
				env->DeleteLocalRef(jstring_InputString);
			}


			// Java のクラス nature_prhysm_controller の参照を削除
			env->DeleteLocalRef(jclass_nature_prhysm_controller);

			// JavaVM とソフト実行用スレッドの関連付け終了
			NativeActivity->vm->DetachCurrentThread();

			if (InputEnd == 1) {//入力を受け取ったらwhile抜けてメインループへ
				strcpy(IP, InputString);//IPアドレスをコピー

				fp = fopen(FilePath, "w");
				if (fp != NULL) {
					fputs(IP, fp);//現在のIPアドレスを保存
					fclose(fp);
				}
				break;
			}
		}
	}
	


}