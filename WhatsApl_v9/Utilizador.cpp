#include "headers.h"


Utilizador::Utilizador(){}

Utilizador::Utilizador(string login, string nome, string email, string nTelemovel){
	Data d;
	this -> login = login;
	this -> nome = nome;
	this -> email = email;
	this -> nTelemovel = nTelemovel;
	dataAdesao = d.getDate();
}


string Utilizador::getLogin()const{

	return login;
}

string Utilizador::getNome()const{

	return nome;
}

string Utilizador::getEmail()const{

	return email;
}

string Utilizador::getNTelemovel()const{

	return nTelemovel;
}
string Utilizador::getDataAdesao()const{

	return dataAdesao;

}

vector<Utilizador> Utilizador::getAmigos()const{

	return amigos;
}
void Utilizador::setData(string dataAdesao){

	this->dataAdesao = dataAdesao;
}
void Utilizador::setLogin(string login)
{
	this->login=login;
}

void Utilizador::setNome(string nome)
{
	this->nome=nome;
}

void Utilizador::setNTelemovel(string nTelemovel)
{
	this->nTelemovel=nTelemovel;
}

void Utilizador::showInfo(){

	cout << "login: " << getLogin() << endl;
	cout << "Nome: " << getNome() << endl;
	cout << "Email: " << getEmail() << endl;
	cout << "Numero de tememovel: " << getNTelemovel() << endl;
	cout << "Data de adesao: " << getDataAdesao() << endl;

}

void Utilizador::mostraContactos(vector<Utilizador> amigos){

	for(unsigned int i  = 0; i < amigos.size(); i++){
		cout << setw(20) << left << amigos[i].getLogin()<< setw(20)<< left << amigos[i].getNome() << setw(15)<< left << amigos[i].getEmail();
		cout << setw(15) << left << amigos[i].getNTelemovel() << setw(15)<< left << amigos[i].getDataAdesao()<< endl;
	}
}


bool Utilizador::operator==(Utilizador u1)const{

	if(nome == u1.getNome())
		return true;
	else return false;
}

bool ordena_por_nome(Utilizador A,Utilizador B)
{
    if (A.getNome() < B.getNome())
       return true;
    return false;
}



void Utilizador::infoContacto(Utilizador &person){

	cout << "Nome: " << person.getNome()<< endl;
	cout << "Login: " << person.getLogin()<< endl;
	cout << "Nº telemovel: " << person.getNTelemovel()<< endl;
	cout << "Data de Adesao: " << person.getDataAdesao()<< endl;
}

bool ordena_por_nome_grupo(Grupo A,Grupo B)
{
    if (A.getTitulo() < B.getTitulo())
       return true;
    return false;
}

void Utilizador::ficheiroGrupos(vector<Grupo> grupos){

		ofstream write;

		write.open("Grupos.txt");

		if(write.is_open() == false)
			throw fileNotOpened("Grupos.txt");

		sort(grupos.begin(),grupos.end(),ordena_por_nome_grupo);

		write << setw(15) <<left << "Titulo "<< setw(17) << left << "Moderador ";
		write << "Data de Criacao" << endl << endl;
		for(unsigned int i  = 0; i < grupos.size(); i++){
			write << setw(15) <<left << grupos[i].getTitulo()<< setw(17) << left <<  grupos[i].getModerador().getLogin();
			write << grupos[i].getDataCriacao() << endl;
		}
}

void Utilizador::recebeNotificacao(string mensagem)
{
	notificacoes.push_back(mensagem);
}

void Utilizador::mostraNotificacoes()
{
	if (notificacoes.size()==0)
	{
		cout << "Nao tem notificacoes novas." << endl;
	}
		else if (notificacoes.size()==1)
		{
			cout << "Tem 1 nova notificacao." << endl << endl;
			cout << notificacoes.at(0)<< endl;
		}
		else
		{
			cout << "Tem " << notificacoes.size() << " novas notificacoes." << endl << endl;

			for (unsigned int i = (notificacoes.size() - 1); i >= 0; i--)
			{
				cout << notificacoes.at(i) << endl;
			}
		}
}

void Utilizador::apagaNotificacoes()
{
	notificacoes.clear();
}

/*
 * FAZER:
 * 	-funcao para verificar se o registo foi corretamente efectuado
 * 		 : 9 numeros (n ºtelemovel)
 * 		 : temos o @ no mail  e o .
 * 		 : nome e login, comecam por letra grande
 * 		 : o nome so pode ser uma palavra
 *
 */
