#include "headers.h"

void ficheiroContactos(vector<Utilizador> &amigos){

	ofstream escreve;
	string fich;
	fich = "Utilizadores.txt";
	escreve.open(fich.c_str());

	if(escreve.is_open() == false)
		throw fileNotOpened(fich);

	escreve << setw(17) <<left << "Login"<< setw(15) << left << "Nome" << setw(25)<< left << "E-mail";
	escreve << setw(15)<< left << "nºtelemovel" << setw(14)<< left << "Data de Adesão" <<endl << endl;

	sort(amigos.begin(), amigos.end(), ordena_por_nome);
	for(unsigned int i  = 0; i < amigos.size(); i++){
		escreve << setw(17) <<left << amigos[i].getLogin()<< setw(15) << left << amigos[i].getNome() << setw(25)<< left << amigos[i].getEmail();
		escreve << setw(15) << left << amigos[i].getNTelemovel() << setw(14)<< left << amigos[i].getDataAdesao()<< endl;
	}
}


vector<Utilizador> leUtilizadores(){
	string login;
	string nome;
	string email;
	string nTelemovel;
	string dataAdesao;
	string lixo;
	ifstream contactos;
	string fich;
	vector<Utilizador> conects;
	fich = "Utilizadores.txt";
	contactos.open(fich.c_str());

	if(contactos.is_open()== false)
			throw fileNotOpened(fich);

	getline(contactos, lixo);
	getline(contactos, lixo);

	string conteudo = "";
	while(! contactos.eof()){
		getline(contactos, conteudo);
		stringstream membros(conteudo);
		membros >> login >> nome >> email >> nTelemovel >> dataAdesao;
		Utilizador u(login, nome,  email,  nTelemovel);
		u.setData(dataAdesao);
		conects.push_back(u);
		conteudo = "";
	}

	contactos.close();
	return conects;
}

vector<Grupo> leGrupos(const vector <Utilizador> util){
	vector<Grupo> grupos;
	string titulo;
	string dataCriacao;
	string moderadorNome;
	string lixo;
	ifstream group;
	string fich;
	fich = "Grupos.txt";
	vector<string> h;
	int valor;
	for(int i = 0; i < util.size(); i++){
		h.push_back(util[i].getLogin());
	}

	group.open(fich.c_str());

	if(group.is_open()== false)
		throw fileNotOpened(fich);

	getline(group, lixo);
	getline(group, lixo);
	string conteudo = "";
	while(! group.eof()){
			int valor;
			getline(group, conteudo);
			stringstream cont(conteudo);
			cont >> titulo >> moderadorNome >> dataCriacao ;
			valor = SequentialSearch(h,moderadorNome);
			Grupo u(util[valor],titulo);
			u.setDataCriacao(dataCriacao);
			grupos.push_back(u);
			conteudo = "";
		}

	group.close();
	return grupos;
}

vector<string> leTitulo(){
	string titulo;
	vector<string> titulos;

	string fich = "Conversas.txt";
	ifstream title;

	title.open(fich.c_str());
	if(title.is_open()== false)
		throw fileNotOpened(fich);

	string conteudo = "";
	while(! title.eof()){
		getline(title, conteudo);
		stringstream str(conteudo);
		str >> titulo;
		titulos.push_back(titulo);
	}
	return titulos;
}
void leTudo(WhatsApl &apl){

	try{
		apl.utilizadores = leUtilizadores();
	}
	catch(RespostaNaoAceite<string> &f){
		cout << "Resposta invalida: " << f.getResposta() << endl;
	}

	try{
		apl.grupos = leGrupos(apl.utilizadores);
	}
	catch(RespostaNaoAceite<string> &f){
		cout << "Resposta invalida: " << f.getResposta() << endl;
	}

	try{
		apl.titulos = leTitulo();
	}
	catch(RespostaNaoAceite<string> &f){
		cout << "Resposta invalida: " << f.getResposta() << endl;
	}
}

void NomeUtilizadores(vector<Utilizador> &amigos){

	for(unsigned int i = 0; i < amigos.size(); ++i){
		cout << amigos[i].getNome() << endl;
	}
}

void tituloGrupos(vector<Grupo> grupos){

	for(unsigned int i = 0; i < grupos.size(); ++i){
		cout << grupos[i].getTitulo() << endl;
	}
}
void registarUtilizador(){
	string login;
	string nome;
	string email;
	string nTelemovel;

	cout << "Login: ";
	getline(cin, login);
	cout << "Nome:";
	getline(cin, nome);
	cout << "Email: ";
	getline(cin, email);
	cout << "N telemovel: ";
	getline(cin, nTelemovel);
}

void registarGrupo(){

	string titulo;

	cout << "Titulo: " ;
	getline(cin, titulo);

}

void endereco(){
	cout << "De: ";
	cout << "Para: ";

}

int menu1(){

	int counter = 1;
	int opcao;

	cout << counter << ". Utlizadores" << endl;
	counter++;
	cout << counter << ". Grupo" << endl;
	counter++;
	cout << counter << ". Registar" << endl;
	counter++;
	cout << counter << ". Escrever Mensagem" << endl;
	counter++;
	cout << counter << ". Creditos" << endl;
	counter++;
	cout << counter << ". Sair" << endl;

	cout << "opcao: ";
	cin >> opcao;

	if (opcao <= 0 || opcao > counter)
		throw RespostaNaoAceite<int>(opcao);

	return opcao;
}

int menuUtilizador(){


	int counter = 1;
	int opcao;

	cout << counter << ". Perfil" << endl;		// mostra o perfil da pessoa
	counter++;
	cout << counter << ". Grupos" << endl;		// mostra os grupos a que pertence
	counter++;
	cout << counter << ". Conversas" << endl;	// display das conversas com grupos ou utilizadores
	counter++;
	cout << counter << ". Escrever Mensagem" << endl;	// ??? so precisaria de inserir o destinatario...
	counter++;
	cout << counter << ". voltar atras" << endl;	// para andar para tras no menu

	cout << "opcao: ";
	cin >> opcao;

	if (opcao <= 0 || opcao > counter)
			throw RespostaNaoAceite<int>(opcao);

	return opcao;
}


int menuGrupo(){


	int counter = 1;
	int opcao;

	cout << counter << ". Grupos" << endl;		// mostra os grupos a que pertence
	counter++;
	cout << counter << ". voltar atras" << endl;	// para andar para tras no menu

	cout << "opcao: ";
	cin >> opcao;

	if (opcao <= 0 || opcao > counter)
			throw RespostaNaoAceite<int>(opcao);

	return opcao;
}

int menuRegistar(){


	int counter = 1;
	int opcao;

	cout << counter << ". Novo Utilizador" << endl;
	counter++;
	cout << counter << ". Novo Grupo" << endl;
	counter++;
	cout << counter << ". voltar atras" << endl;

	cout << "opcao: ";
	cin >> opcao;

	if (opcao <= 0 || opcao > counter)
			throw RespostaNaoAceite<int>(opcao);

	return opcao;
}

void creditos(){
	cout << "Trabalho realizado por:" << endl;
	cout << " joao Chaves" << endl << "Mareclo Ferreira" << endl << "Ricardo Neves" << endl;
}

