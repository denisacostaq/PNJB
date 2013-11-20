package com.blogspot.pnjb;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
//import android.app.Activity;
import android.widget.TextView;

public class MainActivity extends Cocos2dxActivity
{
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		//TextView  tv = new TextView(this);
        //tv.setText( stringFromJNI() );
        /*setContentView(tv);*/
	}
	
    static {
         System.loadLibrary("pnjb");
    }
    
    public native String  stringFromJNI();
}
