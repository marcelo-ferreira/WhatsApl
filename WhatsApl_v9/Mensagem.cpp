#include "headers.h"

Data::Data(/*string date*/) //visto que a data vai ser retirada do pc, não é preciso este argumento, certo?
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);
	int year = (now->tm_year + 1900);
	int hour = now->tm_hour;
	int minutes = now->tm_min;

	stringstream ss;
	ss << day << "/" << month << "/" << year << " " ;
	stringstream stemp;
	stemp << hour << ":" << minutes;
	dia = day;
	mes = month;
	ano = year;
	hora = hour;
	min = minutes;
	date = ss.str();
	temp = stemp.str();
}
int Data::getDia() const {
	return dia;
}
int Data::getMes()const {
	return mes;
}
int Data::getAno()const {
	return ano;
}
int Data::getHora()const{
	return hora;
}
int Data::getMin()const{
	return min;
}
string Data::getTemp()const{
	return temp;
}

string Data::getDate()const {
	return date;
}

Mensagem::Mensagem(Utilizador &emi, Utilizador &dest, string msg): Conversa((emi.getNome()+"_"+dest.getNome()))	// suposto acrescentar algo da classe Conversa? Nao tenho parametros publicos que derivam de Conversa...
{
	Data d;
	data = d.getDate();
	hora = d.getTemp();
	emissor = emi.getNome();
	destinatario = dest.getNome();
	mensagem = msg;
	stringstream noti;
	noti << emi.getNome() << " enviou-te uma mensagem.";
	dest.recebeNotificacao(noti.str());
}

Mensagem::Mensagem(Utilizador &emi, Grupo &group, string msg): Conversa(group.getTitulo())
{

	Data d;
	data = d.getDate();
	hora = d.getTemp();
	emissor = emi.getNome();
	destinatario = group.getTitulo();
	mensagem = msg;
	stringstream noti;
	noti <<"Tem uma nova mensagem no grupo " << destinatario << " enviada por " << emi.getNome();

	for (unsigned i=0;i<group.getMembros().size();i++)
	{
		group.getMembros().at(i).recebeNotificacao(noti.str());
	}

}
string Mensagem::getData()const {
	return data;
}
string Mensagem::getHora()const {
	return hora;
}
string Mensagem::getEmissor()const {
	return emissor;
}
string Mensagem::getDestinatario()const {
	return destinatario;
}

string Mensagem::getMensagem()const {
	return mensagem;
}

bool Mensagem::operator==(Mensagem msg1) const {

	if ((mensagem == msg1.getMensagem()) && (emissor == msg1.getEmissor())
			&& (destinatario == msg1.getDestinatario()))
		return true;
	else
		return false;
}

void Mensagem::displayMensagem(Mensagem &m){


	cout << m.getData() << " | " << m.getHora() << endl;
	cout << m.getMensagem() << endl;

}

/*
 * Penso que esta OK
 */
