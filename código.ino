#define trig 2
#define echo 3
#define buzzer 4
const float DIST_MIN = 3.0;
const float DIST_MAX = 20.0;
const long INTERVALO_MIN = 50;
const long INTERVALO_MAX = 500;
unsigned long tempoAnterior = 0;
long intervaloBuzzer = INTERVALO_MAX;
int estadoBuzzer = LOW;
void setup()
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    Serial.println("Tese de Sensor Ultrassônico");
}

void loop()
{
    float distancia = calcular_distancia();
    Serial.print(distancia);
    Serial.println(" cm");
    if (distancia <= 20)
    {
        float dist_limitada = constrain(distancia, DIST_MIN, DIST_MAX);
        intervaloBuzzer = map(
            (long)(dist_limitada * 10),
            (long)(DIST_MIN * 10),
            (long)(DIST_MAX * 10),
            INTERVALO_MIN,
            INTERVALO_MAX);
        intervaloBuzzer = constrain(intervaloBuzzer, INTERVALO_MIN, INTERVALO_MAX);
        unsigned long tempoAtual = millis();
        if (tempoAtual - tempoAnterior >= intervaloBuzzer)
        {
            tempoAnterior = tempoAtual;
            if (estadoBuzzer == LOW)
            {
                estadoBuzzer = HIGH;
            }
            else
            {
                estadoBuzzer = LOW;
            }
            digitalWrite(buzzer, estadoBuzzer);
            intervaloBuzzer = 4000;
            intervaloBuzzer /= distancia;
        }
    }
    else
    {
        digitalWrite(buzzer, LOW);
    }
}

float calcular_distancia()
{
    long duracao;
    float distancia;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duracao = pulseIn(echo, HIGH);
    distancia = duracao / 58.2;
    return distancia;
}
