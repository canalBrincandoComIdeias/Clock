//Structure and type to store a time
typedef struct {
  byte hora;
  byte minuto;
  byte segundo;
} horario;

// How many thousandths of a second does a day have
#define milesimosNoDia 86400000

// definition of the Clock class
class Clock {
  public:
	Clock(byte horaInicial = 0, byte minutoInicial = 0, byte segundoInicial = 0);
	
	//Set the time (for use in SETUP)
	void ajustaHorario(byte hora, byte minuto, byte segundo = 0);

	// Returns the current time
	horario horarioAtual();

	// Comparisons between two schedules
	bool horarioMenor(horario valor1, horario valor2);
	bool horarioMaior(horario valor1, horario valor2);
	bool horarioMenorOuIgual(horario valor1, horario valor2);
	bool horarioMaiorOuIgual(horario valor1, horario valor2);	
	bool horarioIgual(horario valor1, horario valor2);
	bool horaMinutoIgual(horario valor1, horario valor2);

	//Adicao
	horario adicionaHoras(horario origem, int horas);
	horario adicionaMinutos(horario origem, int minutos);
	horario adicionaSegundos(horario origem, int segundos);
	horario adicionaMilesimos(horario origem, int milesimos);

	//Conversão
	uint32_t horarioParaMilesimo(horario origem);
	uint32_t horarioParaSegundos(horario origem);
	uint32_t horarioParaMinutos(horario origem);
	horario milesimoParaHorario(uint32_t origem);
	String horaParaTexto(horario origem);

	//Set clock when millis() resets (every 50 days approx.)
	void quandoMillisZerar();


  private:
	uint32_t milesimoInicial;
	String strZero(int valor, byte digitos);
	
};