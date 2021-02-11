package com.nature_prhysm_controller.Packaging;

import android.app.NativeActivity;
import android.os.Bundle;
import android.widget.EditText;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import java.lang.Runnable;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetSocketAddress;
import java.net.InetAddress;
import java.io.BufferedReader; 
import java.io.InputStreamReader;
import java.io.IOException;

import android.app.Activity;
import android.media.AudioManager;
import android.media.ToneGenerator;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;


public class nature_prhysm_controller extends NativeActivity
{
	NativeActivity AppActivity ;
	EditText EditView ;
	AlertDialog.Builder AlBuilder ;

	// 入力された文字列を保存するメンバー変数
	String InputString ;

	// 文字列の入力が終わったら 1 にするフラグ用変数
	int InputEnd ;





	// 文字列入力ダイアログを開始する
	public void StartInputStringDialog()
	{
		// NativeActivity の参照をメンバー変数に保存しておく
		AppActivity = this ;

		// 文字列の入力が終わったら 1 にするフラグを 0 で初期化
		InputEnd = 0 ;

		// UIスレッドで実行する処理を登録する
		runOnUiThread( new Runnable ()
		{
			// UIスレッドで呼ばれる関数
			@Override public void run()
			{
				// 文字列入力の View を作成
				EditView = new EditText( AppActivity ) ;

				// ダイアログを作成
				AlBuilder = new AlertDialog.Builder( AppActivity ) ;

				// ダイアログのタイトルを設定
				AlBuilder.setTitle( "PCのIPアドレスを入力してください" ) ;

				// ダイアログに文字列の View をセット
				AlBuilder.setView( EditView ) ;

				// ダイアログに OK ボタンを追加
				AlBuilder.setPositiveButton( "OK", new DialogInterface.OnClickListener()
				{
					// OK ボタンが押されたときに呼ばれる関数
					public void onClick( DialogInterface dialog, int whichButton )
					{
						// 入力された文字列をメンバー変数に保存
						InputString = EditView.getText().toString() ;

						// 入力されたかどうかのフラグを立てる
						InputEnd = 1 ;

						// タイトルバーとナビゲーションバーを非表示にする処理
						View decor = AppActivity.getWindow().getDecorView() ;
						decor.setSystemUiVisibility(
							View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
							View.SYSTEM_UI_FLAG_LOW_PROFILE |
							View.SYSTEM_UI_FLAG_FULLSCREEN |
							View.SYSTEM_UI_FLAG_IMMERSIVE |
							View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY );
					}
				});

				// ダイアログを表示
				AlBuilder.show() ;
			}
		}) ;
	}



	public static final int SERVER_PORT = 4000;
	public static final int PACKET_SIZE = 32;

		private StringBuffer cbuf = new StringBuffer(128);
				int n;
				private DatagramSocket ds; 
				private DatagramPacket dp;
				private String IP_remote;
				private int port_remote;


	// UDPを開始する
	public void send_UDP(final String args,final String button)
	{
	
		// NativeActivity の参照をメンバー変数に保存しておく
		AppActivity = this ;

		// 文字列の入力が終わったら 1 にするフラグを 0 で初期化
		InputEnd = 0 ;

		// UIスレッドで実行する処理を登録する
		runOnUiThread( new Runnable ()
		{
			// UIスレッドで呼ばれる関数
			@Override public void run()
			{
				IP_remote = args; //IPアドレス
				port_remote = 50000;       //ポート番号    
			    
				// UDP　送信                     
				new Thread(new Runnable() {
					public void run() {   
						try {
							InetAddress host = InetAddress.getByName(IP_remote);
							String message = button + " \n";  // 送信メッセージ     
							ds = new DatagramSocket();  //DatagramSocket 作成
							byte[] data = message.getBytes();
							dp = new DatagramPacket(data, data.length, host, port_remote);  //DatagramPacket 作成     
							ds.send(dp);
							//tv2.setText("送信完了しました");
							//InputEnd=-2;		
						}
						catch (Exception e) {
							//System.err.println("Exception : " + e);
							//tv2.setText("送信失敗しました");
							//InputEnd=2;
						}
					}
				}).start();
			}
		}) ;
	}
}