
// Pinos ===================================
const int pinoLuzUV = 2;
const int pinoSensorDeUmidade = A0;
const int pinoBombaDeAgua = 3;
//==========================================

// Luz UV ==================================
bool luzUVLigada = false;
const unsigned long tempoDeDuracao = 10 * 1000; // 10 segundos
const unsigned long tempoParaLigar = 5 * 1000; // 5 segundos
unsigned long tempoInicial = 0;
unsigned long* tempoDeReferencia = &tempoParaLigar;
//==========================================

// Bomba de agua ===========================
const byte porcentagemDeAgua[5] = {255, 204, 153, 102, 51}; //100%, 80%, 60%, 40%, 20%
//==========================================
void setup() {
  //Teste
  Serial.begin(9600);

  pinMode(pinoLuzUV, OUTPUT);
  pinMode(pinoSensorDeUmidade, INPUT);
  pinMode(pinoBombaDeAgua, OUTPUT);

  //Timer
  tempoInicial = millis();
}

void loop() {
  UVLight();
  WaterBombManager();
}

void UVLight(){
  if(millis() - tempoInicial >= *tempoDeReferencia){
    switchUV();
  }
}

void WaterBombManager(){
  unsigned short umidade = analogRead(pinoSensorDeUmidade);
  Serial.println(umidade);

  if(umidade >= 800){       // 100%
    analogWrite(pinoBombaDeAgua, porcentagemDeAgua[0]);
  }else if(umidade >= 600){ // 80%
    analogWrite(pinoBombaDeAgua, porcentagemDeAgua[1]);
  }else if(umidade >= 400){ // 60%
    analogWrite(pinoBombaDeAgua, porcentagemDeAgua[2]);
  }else if(umidade >= 200){ // 40%
    analogWrite(pinoBombaDeAgua, porcentagemDeAgua[3]);
  }else{                    // 20%
    analogWrite(pinoBombaDeAgua, porcentagemDeAgua[4]);
  }
}
void switchUV(){
  if(!luzUVLigada){ 
    digitalWrite(pinoLuzUV, HIGH);
    tempoDeReferencia = &tempoDeDuracao;
  }else{
    digitalWrite(pinoLuzUV, LOW);
    tempoDeReferencia = &tempoParaLigar;
  }

  tempoInicial = millis();
  luzUVLigada = !luzUVLigada;
}
