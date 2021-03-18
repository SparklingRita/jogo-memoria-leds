#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 10, 9, 8, 7); //parametros (RS, Enable, DB4, DB5, DB6, DB7)

int array[50];
int jogada = 0;
int toggle = 2;
int verify;
int score = 0;

void esperarLEDS() //função que cria a sequência de luzes
{

    int randNum = random(3); //gera um número aleatório entre {0,1,2}

    array[jogada] = randNum;
    jogada++;

    delay(1000);

    for (int i = 0; i < jogada; i++)
    {

        if (array[i] == 0) //associar o número 0 ao LED 13
        {
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            digitalWrite(11, LOW);
        }

        if (array[i] == 1) //associar o número 1 ao LED 12
        {
            digitalWrite(13, LOW);
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
        }

        if (array[i] == 2) //associar o número 2 ao LED 11
        {
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);
            digitalWrite(11, HIGH);
        }
        delay(500);

        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);

        delay(500);
    }

    toggle = 1; //passa para o proximo estado de jogo , para executar a função esperarJogador()
}

void esperarJogador()
//função que permite a jogada do jogador e verifica se esta está correta (e o jogo continua)
//ou está errada e o jogo acaba.
{

    if (digitalRead(4) == HIGH) //associar o botão 4 ao led 11 -> número 2
    {
        digitalWrite(11, HIGH);

        if (array[verify] == 2)
        {
            verify++;
            delay(500);
            digitalWrite(11, LOW);
            delay(500);
        }

        else
        {
            gameOver();
        }
    }

    if (digitalRead(5) == HIGH)
    {
        digitalWrite(12, HIGH);

        if (array[verify] == 1)
        {
            verify++;
            delay(500);
            digitalWrite(12, LOW);
            delay(500);
        }

        else
        {
            gameOver();
        }
    }

    if (digitalRead(6) == HIGH)
    {
        digitalWrite(13, HIGH);

        if (array[verify] == 0)
        {
            verify++;
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
        }

        else
        {
            gameOver();
        }
    }

    if (verify == jogada) //para passar à proxima ronda
    {
        toggle = 0; //para que volte a executar a função esperarLEDS();
        verify = 0;
        score = score + 10;

        lcd.setCursor(7, 0);
        lcd.print(score);
    }
}

void startGame()
//função para haver um "Menu" , o jogo só começa quando o jogador
//clickar num botão
{

    lcd.setCursor(0, 0);
    lcd.print("Clica num botao");
    lcd.setCursor(2, 1);
    lcd.print("para comecar");

    if (digitalRead(4) == HIGH || digitalRead(5) == HIGH || digitalRead(6) == HIGH)
    //independentemente do botão carregado, ele irá executar o codigo dentro do if
    {
        lcd.clear();
        lcd.print("Score: ");
        toggle = 0;
    }
}

void gameOver()
//quando o jogador erra a sequência, os 3 LED's piscam e o jogo recomeça
{

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Game Over");
    lcd.setCursor(0, 1);
    lcd.print("Score Total: ");
    lcd.print(score);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(300);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(300);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(300);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(600);

    jogada = 0;
    verify = 0;
    score = -10;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Score: ");
}

void setup()
{
    //Leds
    pinMode(13, OUTPUT); //vermelho
    pinMode(12, OUTPUT); //azul
    pinMode(11, OUTPUT); //verde

    //Buttons
    pinMode(4, INPUT); //direita
    pinMode(5, INPUT); //meio
    pinMode(6, INPUT); //esquerda

    lcd.begin(16, 2);
}

//a variavel toggle controla os 3 estados de jogo
void loop()
{
    if (toggle == 2)
    {
        startGame();
    }

    if (toggle == 0)
    {
        esperarLEDS();
    }

    if (toggle == 1)
    {
        esperarJogador();
    }
}