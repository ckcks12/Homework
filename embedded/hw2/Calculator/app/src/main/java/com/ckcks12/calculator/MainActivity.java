package com.ckcks12.calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.RadioButton;

import java.math.BigDecimal;

public class MainActivity extends AppCompatActivity implements View.OnClickListener
{
    private final String TAG = "eunchan";
    private Calculator calculator = new Calculator();

    private TextView tv;
    private RadioButton radioDecimal;
    private RadioButton radioHeximal;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv = (TextView) findViewById(R.id.tv);
        radioDecimal = (RadioButton) findViewById(R.id.radioDecimal);
        radioHeximal = (RadioButton) findViewById(R.id.radioHeximal);
    }

    private void addText(String s)
    {
        if( tv.getText().equals("0") )
            tv.setText(s);
        else
            tv.append(s);
    }

    private void addText(int n)
    {
        addText(String.valueOf(n));
    }

    private void clearText()
    {
        tv.setText("0");
    }

    private void changeRadix(int radix)
    {
        String tmp = tv.getText().toString();
        BigDecimal big;

        Double d;
        d = Double.parseDouble(tmp);

        switch( radix )
        {
            case 10:
                tmp = d.toString();
                break;
            case 16:
                tmp = Double.toHexString(d);
                break;
        }

        tv.setText(tmp);
    }

    @Override
    public void onClick(View view)
    {
        switch( view.getId() )
        {
            case (R.id.btn0):
                addText(0);
                break;
            case (R.id.btn1):
                addText(1);
                break;
            case (R.id.btn2):
                addText(2);
                break;
            case (R.id.btn3):
                addText(3);
                break;
            case (R.id.btn4):
                addText(4);
                break;
            case (R.id.btn5):
                addText(5);
                break;
            case (R.id.btn6):
                addText(6);
                break;
            case (R.id.btn7):
                addText(7);
                break;
            case (R.id.btn8):
                addText(8);
                break;
            case (R.id.btn9):
                addText(9);
                break;

            case (R.id.btnPlus):
                addText("+");
                break;
            case (R.id.btnMinus):
                addText("-");
                break;
            case (R.id.btnMultiply):
                addText("*");
                break;
            case (R.id.btnDivide):
                addText("/");
                break;
            case (R.id.btnDot):
                addText(".");
                break;

            case (R.id.radioDecimal):
                changeRadix(10);
                radioHeximal.setChecked(false);
                break;
            case (R.id.radioHeximal):
                changeRadix(16);
                radioDecimal.setChecked(false);
                break;

            case (R.id.btnEqual):
                tv.setText(calculator.calculate(tv.getText().toString()));
                if( radioDecimal.isChecked() )
                    changeRadix(10);
                else if( radioHeximal.isChecked() )
                    changeRadix(16);
                break;

            case (R.id.btnClear):
                clearText();
                break;

            case (R.id.btnLeftParen):
                addText("(");
                break;
            case (R.id.btnRightParen):
                addText(")");
                break;
        }
    }
}
