//Estrutura e tipo para armazenar um horario
typedef struct {
  byte hora;
  byte minuto;
  byte segundo;
} horario;

//Quantos milesimos de segundos um dia possui
#define milesimosNoDia 86400000

//definição da classe Clock
class Clock
{
  public:
    Clock();
	
	//Acerta o horario (para uso no SETUP)
	void ajustaHorario(byte hora, byte minuto, byte segundo);

	//Retorna o horario atual
	horario horarioAtual();

	//Comparações entre dois horarios
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

	//Ajuste do relogio quando o millis() zerar (a cada 50 dias aprox.)
	void quandoMillisZerar();


  private:
    uint32_t milesimoInicial;
	String strZero(int valor, byte digitos);
	
};