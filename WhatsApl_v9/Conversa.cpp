#include "headers.h"


Conversa::Conversa(string titulo){
	this->titulo = titulo;
}

string Conversa::getTitulo()const{

	return titulo;
}
void Conversa::display_conversa()
{
	for (unsigned int i=0;i<msg.size();i++)
	{
		cout << msg[i].getMensagem() << endl;
	}
}
/*
void Conversa::escreveTitulos(){

// escrever os titulos no ficheiro;
}
*/
void Conversa::escreveConversa(vector<Mensagem> msg){
	ofstream escreve;
	string indice;

	string ficheiro = titulo + ".txt";

	escreve.open(ficheiro.c_str());

	if(escreve.is_open() == false)
			throw fileNotOpened(ficheiro);

	for(int i = 0 ; i < msg.size(); i++){

		escreve << "De: " << msg[i].getEmissor() << endl;
		escreve << "Para: " << msg[i].getDestinatario() << endl;
		escreve << msg[i].getData() << " | " << msg[i].getHora()<< endl;
		escreve << msg[i].getMensagem() << endl << endl;
	}
}
void Conversa::adiciona_mensagem(Mensagem mens, vector<Mensagem> &msg)
{
	msg.push_back(mens);

}

void Conversa::elimina_mensagem(Mensagem mens)
{
	for (unsigned int i=0; i<msg.size();i++)
		{
			if (mens==msg[i])
				msg.erase(msg.begin()+i);
		}
}

vector<Mensagem> Conversa:: getMesg()const{

	return msg;
}


/*
 * FAZER:
 * 	- Arranjar forma de identificar o ficheiro (done,  e pelo titulo);
 * 	- ler o ficheiro das conversas para um vetor
 */
