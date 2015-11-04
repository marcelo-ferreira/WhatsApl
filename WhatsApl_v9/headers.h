#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>


using namespace std;

class Grupo;
class Mensagem;
class Conversa;

class Utilizador
{
	protected:
		string login;
		string nome;
		string email;
		string nTelemovel;
		string dataAdesao;
		vector<Utilizador> amigos;
		vector<string> notificacoes;
		//vector<Grupo> grupos;
	public:
		Utilizador();
		Utilizador(string login, string nome, string email, string nTelemovel);
		string getLogin()const;
		string getNome()const;
		string getEmail()const;
		string getNTelemovel()const;
		string getDataAdesao()const;
		vector<Utilizador> getAmigos()const;
		void setData(string dataAdesao);
		void setLogin(string login);
		void setNome(string nome);
		void setNTelemovel(string nTelemovel);
		void showInfo();		// efeito de debug
		void mostraContactos(vector<Utilizador> amigos);	// faz o cout da inf dos contactos
		bool operator==(Utilizador u1)const;
		void infoContacto(Utilizador &person);	//informacao de um dos contactos
		bool operator >(Utilizador u1)const;
		void ficheiroGrupos(vector<Grupo> grupos);
		void recebeNotificacao(string mensagem);
		void mostraNotificacoes();
		void apagaNotificacoes();


};

class Grupo
{
	protected:
		string titulo;
		string dataCriacao;
		Utilizador moderador;
		vector<Utilizador> membros;
		vector<Grupo> grupos;
		vector<Utilizador> pedidos;

	public:
		Grupo();
		Grupo(Utilizador moderador, string titulo);
		string getTitulo() const;
		string getDataCriacao() const;
		void setTitulo(string titulo);
		void setDataCriacao(string dataCriacao);
		Utilizador getModerador() const;
		vector<Utilizador> getMembros() const;
		vector<Grupo> getGrupos() const;
		void eliminaGrupo(vector<Grupo> &grupos, Grupo g);
		void ficheiroMembros(vector<Utilizador> membros);
		//bool aceitaMembro( Utilizador u2);
		void pedidoAdesao(Utilizador &membro);
		void vePedidos(Utilizador moderador);
		void leFicheiro(vector<Utilizador> &membros);

};

class Conversa: public Grupo, public Utilizador{
protected:
	vector<Mensagem> msg;
	string titulo;
public:
	Conversa(string titulo);
	vector<Mensagem> getMesg()const;
	string getTitulo()const;
	void display_conversa();
	void adiciona_mensagem(Mensagem mens,vector<Mensagem> &msg);
	void elimina_mensagem(Mensagem mens);
	void escreveConversa(vector<Mensagem> m);
};


class Mensagem: public Conversa{

private:
	string data;
	string hora;
	string emissor;
	string destinatario;
	string mensagem;
public:
	Mensagem(Utilizador &emi, Grupo &group, string msg);
	Mensagem(Utilizador &emi, Utilizador &dest, string msg);
	string getData()const;
	string getHora()const;
	string getDestinatario()const;
	string getEmissor()const;
	string getMensagem()const;
	bool operator==(Mensagem msg1) const;
	void displayMensagem(Mensagem &m);
};

class WhatsApl
{
public:
	WhatsApl();
	vector<Utilizador> utilizadores;
	vector<Grupo> grupos;
	vector<string> titulos;
};

class Data
{
	int dia;
	int mes;
	int ano;
	int hora;
	int min;
	string temp;
	string date;
public:
	Data();
	int getDia()const;
	int getMes()const;
	int getAno()const;
	int getHora()const;
	int getMin()const;
	string getTemp()const;
	string getDate()const;

};


template <class T>
void adiciona(vector<T> &v, T pessoa){		// contacto ou grupo

	v.push_back(pessoa);
}

template <class T>
void elimina(vector<T> &membros, T member){			// so serve para eliminar membros
	for (unsigned int i=0; i<membros.size();i++)
		{
			if (member.getLogin()== membros[i].getLogin()){
				membros.erase(membros.begin()+i);
				i--;
			}
		}													// contacto ou grupo
}


// funcoes auxiliares
void ficheiroContactos(vector<Utilizador> &amigos);
void leUtilizadores(vector<Utilizador> &conects);
void leGrupos(vector<Grupo> &conects, const vector <Utilizador> util);
bool ordena_por_nome_grupo(Grupo A,Grupo B);
bool ordena_por_nome(Utilizador A,Utilizador B);
void registarUtilizador();
void registarGrupo();
void endereco();
int menu1();
int menuUtilizador();
int menuGrupo();
int menuRegistar();
void NomeUtilizadores(vector<Utilizador> &amigos);
void tituloGrupos(vector<Grupo> grupos);
void creditos();

// Classes para tratamento de excecoes

template <class T>
class RespostaNaoAceite{
	T resposta;
public:
	RespostaNaoAceite(T resposta){
		this -> resposta = resposta;
	}
	T getResposta()const{
		return resposta;
	}
};
class loginJaExiste{
	string login;
public:
	loginJaExiste(string login){
		this->login = login;
	}
	string getLogin()const{
		return login;
	}
};

class fileNotOpened{
	string name;
public:
	fileNotOpened(string name){
		this->name = name;
	}
	string getNome()const{
		return name;
	}
};

class NaoeModerador{
	string name;
public:
	NaoeModerador(string name){
		this->name = name;
	}
	string getNome()const{
		return name;
	}
};


// ORDENACAO

template <class T>
int SequentialSearch(const vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;// encontrou
	return -1; // não encontrou
}

template <class Comparable>
void quickSort(vector<Comparable> &v)
{
	quickSort(v,0,v.size()-1);
}

template <class Comparable>
void quickSort(vector<Comparable> &v, int left, int right)
{
	if (right-left <= 10) // se vetor pequeno
		insertionSort(v,left,right);
	else {
		Comparable x = median3(v,left,right); // x ï¿½ o pivot
		int i = left; int j = right-1; // passo de partiï¿½ï¿½o
		for(; ; ) {
			while (v[++i] < x) ;
			while (x < v[--j]) ;
			if (i < j)
				swap(v[i], v[j]);
			else break;
		}
		swap(v[i], v[right-1]); //repoe pivot
		quickSort(v, left, i-1);
		quickSort(v, i+1, right);
	}
}
/*******************************************/


