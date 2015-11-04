#include "headers.h"


Grupo::Grupo(){}

Grupo::Grupo(Utilizador moderador, string titulo){
	Data d;
	this->titulo = titulo;
	this->moderador=moderador;
	dataCriacao = d.getDate();
	membros.push_back(moderador);
}
string Grupo::getTitulo()const
{
	return titulo;
}

string Grupo::getDataCriacao()const
{
	return dataCriacao;
}

Utilizador Grupo::getModerador()const
{
	return moderador;
}

vector<Utilizador> Grupo::getMembros()const{

	return membros;
}

vector<Grupo> Grupo::getGrupos()const{

	return grupos;
}

void Grupo:: setTitulo(string titulo){

	this->titulo = titulo;
}

void Grupo::setDataCriacao(string dataCriacao){

	this->dataCriacao = dataCriacao;
}
void Grupo::eliminaGrupo(vector<Grupo> &grupos, Grupo g){
	for (unsigned int i=0; i<grupos.size();i++)
	{
		if (g.getTitulo()== grupos[i].getTitulo()){
			grupos.erase(grupos.begin()+i);
			i--;
		}
	}
}

void Grupo::leFicheiro(vector<Utilizador> &membros){

	string login;
	string nome;
	string email;
	string nTelemovel;
	string dataAdesao;
	string lixo;
	ifstream contactos;
	string fich;
	fich = getTitulo() + "Membros.txt";
	contactos.open(fich.c_str());

	if(contactos.is_open()== false)
			throw fileNotOpened(fich);

	getline(contactos, lixo);
	getline(contactos, lixo);
	getline(contactos, lixo);
	getline(contactos, lixo);

	string conteudo = "";
	while(! contactos.eof()){
		getline(contactos, conteudo);
		stringstream m(conteudo);
		m >> login >> nome >> email >> nTelemovel >> dataAdesao;
		Utilizador u(login, nome,  email,  nTelemovel);
		u.setData(dataAdesao);
		membros.push_back(u);
		conteudo = "";
	}

	contactos.close();
}
void Grupo::ficheiroMembros(vector<Utilizador> membros){

	ofstream write;
	string fich = "Grupo";
	fich = getTitulo();
	fich += "Membros.txt";
	write.open(fich.c_str());

	if(write.is_open() == false)
			throw fileNotOpened(fich);

	write << "Grupo: " << getTitulo() << endl << endl;
	write << setw(13) <<left << "Login"<< setw(13) << left << "Nome" << setw(27)<< left << "E-mail";
	write << setw(15)<< left << "nº telemovel" << setw(15)<< left << "Data de Adesão" <<endl << endl;

		sort(membros.begin(), membros.end(), ordena_por_nome);
		for(unsigned int i  = 0; i < membros.size(); i++){
			write << setw(13) <<left << membros[i].getLogin()<< setw(13) << left << membros[i].getNome() << setw(27)<< left << membros[i].getEmail();
			write << setw(15)<< left << membros[i].getNTelemovel() << setw(15)<< left << membros[i].getDataAdesao() << endl;
		}

}
/*
bool Grupo::aceitaMembro(Utilizador u2){

	string resposta;
	bool aceite;
	//Esta funcao deve apenas dizer se o moderador aceita ou nao um membro no grupo
	cout << u2.getLogin() << "pretende entrar no grupo, aceitar our recusar (S/N): ";
	getline(cin, resposta);

	if(resposta != "S" && resposta != "N")
		throw RespostaNaoAceite<string>(resposta);

	if(resposta == "S")
		aceite = true;
	else aceite =  false;

	return aceite;
}
*/
void Grupo::pedidoAdesao(Utilizador &membro)
{
	stringstream s1;
	s1 << membro.getNome() << " enviou-te um pedido de adesao ao grupo " << titulo;
	membros.at(0).recebeNotificacao(s1.str());
	pedidos.push_back(membro);
}

void Grupo::vePedidos(Utilizador moderador)
{
	if ((moderador == membros.at(0))== false)
		throw NaoeModerador(moderador.getNome());
	// ATENCAO PODE NAO SER O PRIMEIRO PORQUE O VETOR E ORDENADO!!!!

	cout << "Digite (s) para adicionar e (n) para rejeitar:" << endl << endl;

	while(!pedidos.empty())
	{
		cout << pedidos.at(0).getNome() << "  ";
		string s;
		stringstream msg;
		cin >> s;
		if(s != "s" && s != "n")
			throw RespostaNaoAceite<string>(s);

		if (s=="s")
		{
			msg << "Foi aceite no grupo " << titulo;
			membros.push_back(pedidos.at(0));
		}
		else
		{
			msg << "O seu pedido de adesao ao grupo " << titulo << " nao foi aceite.";
		}

		pedidos.at(0).recebeNotificacao(msg.str());
		pedidos.erase(pedidos.begin());
		cout << endl;
	}
}


/*FAZER:
 * Fazer funcoes, para bloquear o utilizador,  em relacao ao grupo
 * Guardar essa informacao (no ficheiro, o numero de vezes)
 * Ao bloquear o utilizador, nem pode ver o a conversa,  nem enviar mensagens para o grupo
 * Verificar o correto registo
 */
