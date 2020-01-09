#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
	try
	{
		easy.inici();
		answers.resize(0);
		answers.push_back(easy.inici());
		for (nat i = 0; i < input.size(); ++i)
		{
			if (input[i] == phone::DELETECHAR)
			{
				easy.anterior();
				if (answers.size() > 1)
					answers.pop_back();
			}
			else if (input[i] == phone::ENDCHAR)
			{
				if (answers.size() > 1)
					answers.push_back(easy.seguent(phone::ENDPREF));
			}
			else
				answers.push_back(easy.seguent(input[i]));
		}
		numtelf = easy.num_telf();
	}
	catch(error e)
	{
		answers.push_back(e.mensaje());
		numtelf = 0;
		return;
	}

}