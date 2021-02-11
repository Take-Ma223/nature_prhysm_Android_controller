#include "DxLib.h"
#include"Controller.h"
#include<string.h>

// プログラムは android_main から始まります
int android_main(void)
{
	SetOutApplicationLogValidFlag(FALSE);//ログ出力を行わない

	SetGraphMode(1280, 720, 16);//画面サイズは1280*720

	SetWaitVSyncFlag(FALSE);//垂直同期は行わない
	SetAlwaysRunFlag(TRUE);//非アクティブでも動作




	// 背景を灰色にする
	SetBackgroundColor(128, 128, 128);

	//SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);


	

	/*
	// メインループ
	while (ProcessMessage() == 0)
	{
		// 裏画面の内容をクリア
		ClearDrawScreen();

		// 入力が完了していなかったら Java のクラス nature_prhysm_controller のメンバー変数 InputEnd と InputString の情報を取得する
		if (InputEnd == 0)
		{
			// JavaVM とソフト実行用スレッドを関連付け( C++ から Java の機能を使用するために必要 )
			if (NativeActivity->vm->AttachCurrentThreadAsDaemon(&env, NULL) != JNI_OK)
			{
				return -1;
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
		}

		// InputEnd と InputString の状態を画面に描画
		DrawFormatString(0, 100, GetColor(255, 255, 255), "InputEnd:%d  InputString:%s", InputEnd, InputString);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	*/






	Controller Controller;
	Controller.run();


	//Controller();


	DrawBox(220, 140, 420, 340, GetColor(255, 255, 255), TRUE);	// 四角形を描画する

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了 
}