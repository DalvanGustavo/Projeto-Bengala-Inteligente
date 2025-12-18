#define trig_baixo 12
#define echo_baixo 11
#define trig_cima 9
#define echo_cima 6
#define buzzer 4
#define motor_baixo 3
#define motor_cima 2
const float DIST_MIN = 3.0;
const float DIST_MAX = 20.0;
const long INTERVALO_MIN = 50;
const long INTERVALO_MAX = 500;
unsigned long tempo_anterior_buzzer = 0;
unsigned long tempo_anterior_motor_cima = 0;
unsigned long tempo_anterior_motor_baixo = 0;
long intervalo_buzzer = INTERVALO_MAX;
long intervalo_motor_baixo = INTERVALO_MAX;
long intervalo_motor_cima = INTERVALO_MAX;
int estado_buzzer = LOW;
int estado_motor_baixo = LOW;
int estado_motor_cima = LOW;
void setup()
{
    pinMode(trig_baixo, OUTPUT);
    pinMode(echo_baixo, INPUT);
    pinMode(trig_cima, OUTPUT);
    pinMode(echo_cima, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(motor_baixo, OUTPUT);
    pinMode(motor_cima,OUTPUT);
    Serial.begin(9600);
    Serial.println("Tese de Sensor Ultrassônico");
}
void loop()
{
    float distancia_baixo = calcular_distancia_baixo();
    float distancia_cima = calcular_distancia_cima();
    Serial.print(distancia_baixo);
    Serial.println(" cm baixo");
    float menor_valor = min(distancia_baixo, distancia_cima);
    if (menor_valor <= 20)
    {
        float dist_limitada = constrain(menor_valor, DIST_MIN, DIST_MAX);
        intervalo_buzzer = map((long)(dist_limitada * 10), (long)(DIST_MIN * 10), (long)(DIST_MAX * 10), INTERVALO_MIN, INTERVALO_MAX);
        intervalo_buzzer = constrain(intervalo_buzzer, INTERVALO_MIN, INTERVALO_MAX);
        unsigned long tempoAtual = millis();
        if (tempoAtual - tempo_anterior_buzzer >= intervalo_buzzer){
            tempo_anterior_buzzer = tempoAtual;
            if (estado_buzzer == LOW){
                estado_buzzer = HIGH;
            }else{
                estado_buzzer = LOW;
            }
            digitalWrite(buzzer, estado_buzzer);
            intervalo_buzzer = 4000;
            intervalo_buzzer /= menor_valor;
        }
    }else{
        digitalWrite(buzzer, LOW);
    }
    if(distancia_baixo < 50){
        float dist_limitada = constrain(distancia_baixo, DIST_MIN, DIST_MAX);
        intervalo_motor_baixo = map((long)(dist_limitada * 10), (long)(DIST_MIN * 10), (long)(DIST_MAX * 10), INTERVALO_MIN, INTERVALO_MAX);
        intervalo_motor_baixo = constrain(intervalo_motor_baixo, INTERVALO_MIN, INTERVALO_MAX);
        unsigned long tempoAtual = millis();
        if (tempoAtual - tempo_anterior_motor_baixo >= intervalo_motor_baixo){
            tempo_anterior_motor_baixo = tempoAtual;
            if (estado_motor_baixo == LOW){
                estado_motor_baixo = HIGH;
            }else{
                estado_motor_baixo = LOW;
            }
            digitalWrite(motor_baixo, estado_motor_baixo);
            intervalo_motor_baixo = 4000;
            intervalo_motor_baixo /= distancia_baixo;
        }
    }else{
        digitalWrite(motor_baixo, LOW);
    }
    if(distancia_cima < 50){
        float dist_limitada = constrain(distancia_cima, DIST_MIN, DIST_MAX);
        intervalo_motor_cima = map((long)(dist_limitada * 10), (long)(DIST_MIN * 10), (long)(DIST_MAX * 10), INTERVALO_MIN, INTERVALO_MAX);
        intervalo_motor_cima = constrain(intervalo_motor_cima, INTERVALO_MIN, INTERVALO_MAX);
        unsigned long tempoAtual = millis();
        if (tempoAtual - tempo_anterior_motor_cima >= intervalo_motor_cima){
            tempo_anterior_motor_cima = tempoAtual;
            if (estado_motor_cima == LOW){
                estado_motor_cima = HIGH;
            }else{
                estado_motor_cima = LOW;
            }
            digitalWrite(motor_cima, estado_motor_cima);
            intervalo_motor_cima = 4000;
            intervalo_motor_cima /= distancia_cima;
        }
    }else{
        digitalWrite(motor_cima, LOW);
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