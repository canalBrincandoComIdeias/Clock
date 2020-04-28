/*
     CÓDIGO:    D0026
     AUTOR:     BrincandoComIdeias
     ACOMPANHE: https://brincandocomideias.com/links ; https://youtube.com/brincandocomideias
     REDES:     https://instagram.com/canalBrincandoComIdeias/ ; https://t.me/canal_brincando_com_ideias
     APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:    https://www.arducore.com.br/
     SKETCH:    Schedule
     DATA:      26/04/2020
*/

// INCLUSÃO DE BIBLIOTECA
#include "Clock.h" // DOWNLOAD: https://github.com/canalBrincandoComIdeias/Clock

// DEFINIÇÕES
#define devices 2 // Número de devices

// INSTANCIANDO OBJETOS
Clock meuRelogio;

// DECLARAÇÃO DE VARIÁVEIS
byte pinRele[devices] = {13, 10};         // Pino dos devices, deve ter a mesma quantidade que a definição de devices
bool ligado[devices] = {true, true};    // Estado dos devices, deve ter a mesma quantidade que a definição de devices

int tempoAcionamento[devices] = {2, 3}; // tempo em minutos, deve ter a mesma quantidade que a definição de devices
int tempoIntervalo[devices]   = {1, 2};  // tempo em minutos, deve ter a mesma quantidade que a definição de devices

horario ultimoAcionamento[devices];  // Array para controle de acionamento
horario horarioAcionamento[devices]; // Array para controle de desligamento

// DECLARAÇÃO DE FUNÇÕES
void acionaRele(byte numDevice);
void desligaRele(byte numDevice);

void setup() {
  for (int nL = 0; nL < devices; nL++ ) {
    pinMode(pinRele[nL], OUTPUT);
	acionaRele(nL);
  }

  Serial.begin(9600);
}

void loop() {

  //registra o momento atual
  horario agora = meuRelogio.horarioAtual();
  Serial.println( meuRelogio.horaParaTexto(agora) );

  for (int nL = 0; nL < devices; nL++ ) {
    if (!ligado[nL] ) {
      horario proximoAcionamento = meuRelogio.adicionaMinutos(ultimoAcionamento[nL], tempoAcionamento[nL]);
      bool    temQueAcionar      = meuRelogio.horarioMaiorOuIgual( agora, proximoAcionamento );

      if ( temQueAcionar ) {
        acionaRele(nL);
        horarioAcionamento[nL] = agora;
        ultimoAcionamento[nL]  = agora;
        ligado[nL] = true;
      }
    }

    if (ligado[nL]) {
      horario proximoDesligamento = meuRelogio.adicionaMinutos(horarioAcionamento[nL], tempoIntervalo[nL]);
      bool    temQueDesligar      = meuRelogio.horarioMaiorOuIgual( agora, proximoDesligamento );

      if ( temQueDesligar ) {
        desligaRele(nL);
        ligado[nL] = false;
      }
    }
  }

}
