#include "Arduino.h"
#include "Clock.h"

Clock::Clock() {
}

void Clock::ajustaHorario(byte hora, byte minuto, byte segundo) {
  horario horarioInicial;
  horarioInicial.segundo = segundo; 
  horarioInicial.minuto  = minuto; 
  horarioInicial.hora    = hora;
  milesimoInicial = horarioParaMilesimo(horarioInicial);
}

horario Clock::horarioAtual() {  
  uint32_t milesimoAtual = (milesimoInicial + (millis() % milesimosNoDia));
  return milesimoParaHorario(milesimoAtual);
}

bool Clock::horarioMenor(horario valor1, horario valor2) {
	return horarioParaMilesimo(valor1) < horarioParaMilesimo(valor2);
}

bool Clock::horarioMaior(horario valor1, horario valor2) {
	return horarioParaMilesimo(valor1) > horarioParaMilesimo(valor2);
}

bool Clock::horarioMenorOuIgual(horario valor1, horario valor2) {
	return horarioParaMilesimo(valor1) <= horarioParaMilesimo(valor2);
}

bool Clock::horarioMaiorOuIgual(horario valor1, horario valor2) {
	return horarioParaMilesimo(valor1) >= horarioParaMilesimo(valor2);
}

bool Clock::horarioIgual(horario valor1, horario valor2) {  
	return horarioParaMilesimo(valor1) == horarioParaMilesimo(valor2);
}

bool Clock::horaMinutoIgual(horario valor1, horario valor2) {  
	return horarioParaMinutos(valor1) == horarioParaMinutos(valor2);
}				

horario Clock::adicionaHoras(horario origem, int horas) {
	uint32_t calculo = horarioParaMilesimo(origem);
	calculo += (horas * 3600000);	
	return milesimoParaHorario(calculo);
}

horario Clock::adicionaMinutos(horario origem, int minutos) {
	uint32_t calculo = horarioParaMilesimo(origem);
	calculo += (minutos * 60000);	
	return milesimoParaHorario(calculo);
}

horario Clock::adicionaSegundos(horario origem, int segundos) {
	uint32_t calculo = horarioParaMilesimo(origem);
	calculo += (segundos * 1000);	
	return milesimoParaHorario(calculo);
}

horario Clock::adicionaMilesimos(horario origem, int milesimos) {
	uint32_t calculo = horarioParaMilesimo(origem);
	calculo += milesimos;	
	return milesimoParaHorario(calculo);
}
		
uint32_t Clock::horarioParaMilesimo(horario origem) {
  uint32_t retorno;

  retorno = horarioParaSegundos(origem) * 1000;
  return retorno;
}

uint32_t Clock::horarioParaSegundos(horario origem) {
  uint32_t retorno;

  retorno = horarioParaMinutos(origem) * 60;
  retorno += origem.segundo;

  return retorno;
}

uint32_t Clock::horarioParaMinutos(horario origem) {
  uint32_t retorno;

  retorno =  (uint32_t)origem.hora * 60; 
  retorno += (uint32_t)origem.minuto;

  return retorno;
}

horario Clock::milesimoParaHorario(uint32_t origem) {
  horario retorno;

  origem = origem / 1000;
  retorno.segundo = origem % 60;
  
  origem = origem / 60;
  retorno.minuto  = origem % 60;

  origem = origem / 60;
  retorno.hora  = origem % 24;
  return retorno;
}

String Clock::horaParaTexto(horario origem) {
  String textoRetorno = strZero(origem.hora, 2);
  textoRetorno += ":";
  textoRetorno += strZero(origem.minuto, 2);
  textoRetorno += ":";
  textoRetorno += strZero(origem.segundo, 2);
  return textoRetorno;
}

String Clock::strZero(int valor, byte digitos) {
  String textoRetorno = String(valor);
  while (textoRetorno.length() < digitos ) {
    textoRetorno = "0" + textoRetorno;
  }
  return textoRetorno;
}

void Clock::quandoMillisZerar() {
static uint32_t ultimoMillis;

  if (millis() < ultimoMillis) { //millis zerou
     milesimoInicial += (uint32_t)pow(2, sizeof(uint32_t)*8 ) % milesimosNoDia;        
     milesimoInicial = milesimoInicial % milesimosNoDia;
  }
  ultimoMillis = millis();   
}
