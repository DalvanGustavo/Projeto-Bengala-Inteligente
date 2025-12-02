#define trig_baixo 2
#define echo_baixo 3
#define trig_meio 4
#define echo_meio 5
#define trig_cima 6
#define echo_cima 7
#define buzzer 8
const float DIST_MIN = 3.0;
const float DIST_MAX = 20.0;
const long INTERVALO_MIN = 50;
const long INTERVALO_MAX = 500;
unsigned long tempoAnterior = 0;
long intervaloBuzzer = INTERVALO_MAX;
int estadoBuzzer = LOW;
void setup()
{
    pinMode(trig_baixo, OUTPUT);
    pinMode(echo_baixo, INPUT);
    pinMode(trig_meio, OUTPUT);
    pinMode(echo_meio, INPUT);
    pinMode(trig_cima, OUTPUT);
    pinMode(echo_cima, INPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    Serial.println("Tese de Sensor Ultrassônico");
}
void loop()
{
    float distancia_baixo = calcular_distancia_baixo();
    float distancia_meio = calcular_distancia_meio();
    float distancia_cima = calcular_distancia_cima();
    Serial.print(distancia_baixo);
    Serial.println(" cm baixo");
    float menor_valor = min(distancia_baixo, min(distancia_meio, distancia_cima));
    if (menor_valor <= 20)
    {
        float dist_limitada = constrain(menor_valor, DIST_MIN, DIST_MAX);
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
            intervaloBuzzer /= menor_valor;
        }
    }
    else
    {
        digitalWrite(buzzer, LOW);
    }
}

float calcular_distancia_baixo()
{
    long duracao;
    float distancia;
    digitalWrite(trig_baixo, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_baixo, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_baixo, LOW);
    duracao = pulseIn(echo_baixo, HIGH, 30000);
    distancia = duracao / 58.2;
    return distancia;
}

float calcular_distancia_meio()
{
    long duracao;
    float distancia;
    digitalWrite(trig_meio, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_meio, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_meio, LOW);
    duracao = pulseIn(echo_meio, HIGH, 30000);
    distancia = duracao / 58.2;
    return distancia;
}

float calcular_distancia_cima()
{
    long duracao;
    float distancia;
    digitalWrite(trig_cima, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_cima, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_cima, LOW);
    duracao = pulseIn(echo_cima, HIGH, 30000);
    distancia = duracao / 58.2;
    return distancia;
}
