
/*  LIGADOR
 *  Cristiana Miranda de Farias - 10/0129323
 *  Pedro Henrique Hecksher Faber - 10/0119140
 */


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>






struct use
{
	std::string label;
	std::string end;
};

struct def
{
	std::string label;
	std::string end;
};



int main(int argc, char*argv[]) {
	int num_aux;
	int i, j, k;
	int fc1, fc2;

	std::string palavra;
	std::string arquivo_entrada1;
    std::string arquivo_entrada2;
    std::string arquivo_entrada3;
	std::string arquivo_saida;
	std::string limpa_linha;
    std::vector<std::string> global_label;

	bool istableuse = false;
	bool istabledef = false;
	bool isrelative = false;
	bool iscode = false;
    bool isextern = false;

	std::vector<int> relative1(0);
	std::vector<int> relative2(0);
    std::vector<int> relative3(0);
	std::vector<int> code1(0);
	std::vector<int> code2(0);
    std::vector<int> code3(0);
    std::vector<int> use_end1(0);
    std::vector<int> use_end2(0);
    std::vector<int> use_end3(0);
    std::vector<int> def_end1(0);
    std::vector<int> def_end2(0);
    std::vector<int> def_end3(0);
    std::vector<int> global_end;
    std::vector<int> code_ligado;
    std::vector<int> global_relative(0);

    std::vector<std::string> use_label1(0);
    std::vector<std::string> use_label2(0);
    std::vector<std::string> use_label3(0);
	std::vector<std::string> def_label1(0);
	std::vector<std::string> def_label2(0);
    std::vector<std::string> def_label3(0);
	



	arquivo_entrada1 = argv[1];

	//conta o numero de linhas do primeiro modulo
	std::ifstream inFile1(arquivo_entrada1.c_str());
	int num_lines = std::count(std::istreambuf_iterator<char>(inFile1),
	std::istreambuf_iterator<char>(), '\n');

	num_lines=num_lines+1;

	//pega o arquivo de texto e coloca numa string só
	std::ifstream in1(arquivo_entrada1.c_str());
	std::stringstream buffer;
	buffer << in1.rdbuf();
	std::string modulo1 = buffer.str();


    //criar variaveis que vao agir como cursores
    size_t pos1 = 0;
    size_t pos2;


    //cria um array
    std::string str[num_lines];


    //salva cada linha no vetor de strings str[i]
    for (i=0; i<num_lines; i++)
    {
        pos2 = modulo1.find("\n", pos1); //procura pelo final da linha, pos2 vai ser aonde encontrar.
        str[i] = modulo1.substr(pos1, (pos2-pos1)); //cria um substring
        pos1 = pos2+1; // coloca pos1 no caracter logo depois do pos2
	}






    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////                                    PRIMEIRO MODULO                                             ////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////







    for (i=0; i < num_lines; i++)
    {



        /////////////////////////////////////////////////////////
        // RETIRA ESPAÇOS EM BRANCO ANTES E DEPOIS DE CADA LINHA/
        /////////////////////////////////////////////////////////

        limpa_linha = str[i];



    	while (limpa_linha[limpa_linha.size() - 1] == 32)
    	{

    			limpa_linha = limpa_linha.substr(0, limpa_linha.size() - 1);
    	};

    	while (limpa_linha[0] == 32)
    	{
    			limpa_linha = limpa_linha.substr(1, limpa_linha.size());
    	};


    	if (str[i] == "TABLE USE")
    	{
    		istableuse = true;
    	}

    	else if (str[i] == "TABLE DEFINITION")
		{
			istabledef = true;
	    	istableuse = false;

		}

    	else if (str[i] == "RELATIVE")
		{
			isrelative = true;
	    	istabledef = false;

		}

    	else if (str[i] == "CODE")
		{
			iscode = true;
	    	isrelative = false;

		}



    	std::stringstream is(str[i]);
    	int j=0;
    	while ( is >> palavra)
    	{

    		if (istableuse == true)
    		{
    			if ( j == 0 && palavra != "TABLE")
    			{
    				use_label1.push_back(palavra);
    			}
    			if ( j == 1 && palavra != "USE")
    			{

    				std::stringstream string_aux(palavra);
    				string_aux >> num_aux;
    				use_end1.push_back(num_aux);

    			}
    		}

    		if (istabledef == true )
    		{
    			if ( j == 0 && palavra != "TABLE")
    			{
    				def_label1.push_back(palavra);
    			}
    			if ( j == 1 && palavra != "DEFINITION")
    			{
    				std::stringstream string_aux(palavra);
    				string_aux >> num_aux;
    				def_end1.push_back(num_aux);

    			}
    		}

    		if (isrelative == true && palavra != "RELATIVE")
    		{
				std::stringstream string_aux(palavra);
				string_aux >> num_aux;
				relative1.push_back(num_aux);
    		}

    		if (iscode == true && palavra != "CODE")
    		{
				std::stringstream string_aux(palavra);
				string_aux >> num_aux;
				code1.push_back(num_aux);
    		}
    		j++;
    	}
    }
	iscode = false;







    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////                                    SEGUNDO MODULO                                              ////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////








	if (argc >= 3)
    {
        arquivo_entrada2 = argv[2];


        //conta o numero de linhas do segundo modulo
        std::ifstream inFile2(arquivo_entrada2.c_str());
        int num_lines2 = std::count(std::istreambuf_iterator<char>(inFile2),
        std::istreambuf_iterator<char>(), '\n');

        num_lines2=num_lines2+1;


        //pega o arquivo de texto e coloca numa string só
        std::ifstream in2(arquivo_entrada2.c_str());
        std::stringstream buffer2;
        buffer2 << in2.rdbuf();
        std::string modulo2 = buffer2.str();



        //std::cout << "O número de linhas do segundo módulo é: " << num_lines2 << std::endl;


        //criar variaveis que vao agir como cursores
        pos1 = 0;
        pos2 = 0;


        //cria um array
        std::string str2[num_lines2];


        //salva cada linha no vetor de strings str[i]
        for (i=0; i<num_lines2; i++)
        {
            pos2 = modulo2.find("\n", pos1); //procura pelo final da linha, pos2 vai ser aonde encontrar.
            str2[i] = modulo2.substr(pos1, (pos2-pos1)); //cria um substring
            pos1 = pos2+1; // coloca pos1 no caracter logo depois do pos2
        }



        //define o numero de rotulos na tabela de uso

        /////////////////////////////////////
        //LOOP PRINCIPAL DO SEGUNDO MODULO//
        /////////////////////////////////////


        for (i=0; i < num_lines2; i++)
        {



            /////////////////////////////////////////////////////////
            // RETIRA ESPAÇOS EM BRANCO ANTES E DEPOIS DE CADA LINHA/
            /////////////////////////////////////////////////////////

            limpa_linha = str2[i];



            while (limpa_linha[limpa_linha.size() - 1] == 32)
            {

                    limpa_linha = limpa_linha.substr(0, limpa_linha.size() - 1);
            };

            while (limpa_linha[0] == 32)
            {
                    limpa_linha = limpa_linha.substr(1, limpa_linha.size());
            };


            if (str2[i] == "TABLE USE")
            {
                istableuse = true;
            }

            else if (str2[i] == "TABLE DEFINITION")
            {
                istabledef = true;
                istableuse = false;
            }

            else if (str2[i] == "RELATIVE")
            {
                isrelative = true;
                istabledef = false;

            }

            else if (str2[i] == "CODE")
            {
                iscode = true;
                isrelative = false;

            }



            std::stringstream is(str2[i]);
            int j=0;
            while ( is >> palavra)
            {

                if (istableuse == true)
                {
                    if ( j == 0 && palavra != "TABLE")
                    {
                        use_label2.push_back(palavra);
                    }
                    if ( j == 1 && palavra != "USE")
                    {

                        std::stringstream string_aux(palavra);
                        string_aux >> num_aux;
                        use_end2.push_back(num_aux);

                    }
                }

                if (istabledef == true )
                {
                    if ( j == 0 && palavra != "TABLE")
                    {
                        def_label2.push_back(palavra);
                    }
                    if ( j == 1 && palavra != "DEFINITION")
                    {
                        std::stringstream string_aux(palavra);
                        string_aux >> num_aux;
                        def_end2.push_back(num_aux);

                    }
                }

                if (isrelative == true && palavra != "RELATIVE")
                {
                    std::stringstream string_aux(palavra);
                    string_aux >> num_aux;
                    relative2.push_back(num_aux);
                }

                if (iscode == true && palavra != "CODE")
                {
                    std::stringstream string_aux(palavra);
                    string_aux >> num_aux;
                    code2.push_back(num_aux);
                }
                j++;
            }
        }
        iscode = false;


        
        //////////////////////////////////////////////////////
        //////              FATOR DE CORREÇÃO           //////
        //////////////////////////////////////////////////////



        fc1=code1.size();



        //tabela global de definições
        global_label = def_label1;
        global_end = def_end1;

        for (i = 0; i < def_end2.size(); i++)
        {
            global_label.push_back(def_label2[i]);
            global_end.push_back(def_end2[i]+fc1);
        }

        //adiciona fc em todos os relativos do segundo modulo
        for (i = 0; i < code2.size(); i++)
        {

            for (j = 0; j < relative2.size(); j++)
            {
                if (relative2[j] == i)
                {
                    code2[i]=code2[i]+fc1;
                    //code_ligado.push_back(code2[i]+fc);
                }
            }
        }

        code_ligado = code1;

        for (i = 0; i < code2.size(); i++)
        {
            code_ligado.push_back(code2[i]);
        }    
    }




    /////////////////////////////////////////////////////////////////////////////////////////////
    ///     arruma os relativos globais     /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////


    global_relative = relative1;

    for (i = 0; i < relative2.size(); i++)
    {
        global_relative.push_back(relative2[i] + fc1);
    }                                                        


    //std::cout<<std::endl;
    //std::cout<< fc1 <<std::endl;










    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////                                   TERCEIRO MODULO                                              ////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////








    if (argc == 4)
    {
        arquivo_entrada3 = argv[3];


        //conta o numero de linhas do segundo modulo
        std::ifstream inFile3(arquivo_entrada3.c_str());
        int num_lines3 = std::count(std::istreambuf_iterator<char>(inFile3),
        std::istreambuf_iterator<char>(), '\n');

        num_lines3=num_lines3+1;


        //pega o arquivo de texto e coloca numa string só
        std::ifstream in3(arquivo_entrada3.c_str());
        std::stringstream buffer3;
        buffer3 << in3.rdbuf();
        std::string modulo3 = buffer3.str();



        //std::cout << "O número de linhas do segundo módulo é: " << num_lines2 << std::endl;


        //criar variaveis que vao agir como cursores
        pos1 = 0;
        pos2 = 0;


        //cria um array
        std::string str3[num_lines3];


        //salva cada linha no vetor de strings str[i]
        for (i=0; i<num_lines3; i++)
        {
            pos2 = modulo3.find("\n", pos1); //procura pelo final da linha, pos2 vai ser aonde encontrar.
            str3[i] = modulo3.substr(pos1, (pos2-pos1)); //cria um substring
            pos1 = pos2+1; // coloca pos1 no caracter logo depois do pos2
        }



        //define o numero de rotulos na tabela de uso

        /////////////////////////////////////
        //LOOP PRINCIPAL DO TERCEIRO MODULO//
        /////////////////////////////////////


        for (i=0; i < num_lines3; i++)
        {



            /////////////////////////////////////////////////////////
            // RETIRA ESPAÇOS EM BRANCO ANTES E DEPOIS DE CADA LINHA/
            /////////////////////////////////////////////////////////

            limpa_linha = str3[i];



            while (limpa_linha[limpa_linha.size() - 1] == 32)
            {

                    limpa_linha = limpa_linha.substr(0, limpa_linha.size() - 1);
            };

            while (limpa_linha[0] == 32)
            {
                    limpa_linha = limpa_linha.substr(1, limpa_linha.size());
            };


            if (str3[i] == "TABLE USE")
            {
                istableuse = true;
            }

            else if (str3[i] == "TABLE DEFINITION")
            {
                istabledef = true;
                istableuse = false;
            }

            else if (str3[i] == "RELATIVE")
            {
                isrelative = true;
                istabledef = false;

            }

            else if (str3[i] == "CODE")
            {
                iscode = true;
                isrelative = false;

            }



            std::stringstream is(str3[i]);
            int j=0;
            while ( is >> palavra)
            {

                if (istableuse == true)
                {
                    if ( j == 0 && palavra != "TABLE")
                    {
                        use_label3.push_back(palavra);
                    }
                    if ( j == 1 && palavra != "USE")
                    {

                        std::stringstream string_aux(palavra);
                        string_aux >> num_aux;
                        use_end3.push_back(num_aux);

                    }
                }

                if (istabledef == true )
                {
                    if ( j == 0 && palavra != "TABLE")
                    {
                        def_label3.push_back(palavra);
                    }
                    if ( j == 1 && palavra != "DEFINITION")
                    {
                        std::stringstream string_aux(palavra);
                        string_aux >> num_aux;
                        def_end3.push_back(num_aux);

                    }
                }

                if (isrelative == true && palavra != "RELATIVE")
                {
                    std::stringstream string_aux(palavra);
                    string_aux >> num_aux;
                    relative3.push_back(num_aux);
                }

                if (iscode == true && palavra != "CODE")
                {
                    std::stringstream string_aux(palavra);
                    string_aux >> num_aux;
                    code3.push_back(num_aux);
                }
                j++;
            }
        }
        iscode = false;


        
        //////////////////////////////////////////////////////
        //////              FATOR DE CORREÇÃO           //////
        //////////////////////////////////////////////////////



        fc2 = fc1+ code2.size();



        for (i = 0; i < def_end3.size(); i++)
        {
            global_label.push_back(def_label3[i]);
            global_end.push_back(def_end3[i]+fc2);
        }


        //adiciona fc em todos os relativos do segundo modulo
        for (i = 0; i < code3.size(); i++)
        {
            for (j = 0; j < relative3.size(); j++)
            {
                if (relative3[j] == i)
                {
                    code3[i]=code3[i]+fc2;
                    //code_ligado.push_back(code2[i]+fc);
                }
            }
        }


        for (i = 0; i < code3.size(); i++)
        {
            code_ligado.push_back(code3[i]);
        }    
    }





    /////////////////////////////////////////////////////////////////////////////////////////////
    ///     arruma os relativos globais     /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
                               


    //std::cout<< fc2 <<std::endl;


    for (i = 0; i < relative3.size(); i++)
    {
        global_relative.push_back(relative3[i] + fc2);
    }                                                        



    /*
    for (i = 0; i < relative1.size(); i++)
    {
        std::cout<<relative1[i]<< " ";
    }    
    std::cout<<std::endl;

    for (i = 0; i < relative2.size(); i++)
    {
        std::cout<<relative2[i]<< " ";
    }    

        std::cout<<std::endl;


    for (i = 0; i < relative3.size(); i++)
    {
        std::cout<<relative3[i]<< " ";
    } 
    
        std::cout<<std::endl;


    for (i = 0; i < global_relative.size(); i++)
    {
        std::cout<<global_relative[i]<< " ";
    }    

    std::cout<<std::endl;
    

    */



       for (i = 0; i < code1.size(); i++)
        {
            for (j = 0; j < use_end1.size(); j++)
            {
                if (i == use_end1[j])
                {
                    for (k = 0; k < global_end.size(); k++)
                    {
                        if (use_label1[j] == global_label[k])
                        {
                            //use_end1[j] = global_end[k];
                            code_ligado[i] = code_ligado[i] + global_end[k];
                        }
                    }
                }
            }
        }
        

        /*std::cout<<std::endl;

        for (i=0; i< global_end.size(); i++){
            std::cout<<global_label[i]<< " ";
            std::cout<<global_end[i]<< " ";
            std::cout<<std::endl;

        }
        
        
        std::cout<<std::endl;
        std::cout<<std::endl;
        */


        for (i = code1.size(); i < (code1.size()+code2.size()); i++)
        {
            for (j = 0; j < use_end2.size(); j++)
            {
                if (i == use_end2[j]+fc1)
                {
                    for (k = 0; k < global_end.size(); k++)
                    {
                        if (use_label2[j] == global_label[k])
                        {
                            //use_end1[j] = global_end[k];
                            code_ligado[i] = code_ligado[i] + global_end[k] - fc1;
                        }
                    }
                }
            }
        }


        for (i = (code1.size()+code2.size()); i < (code1.size()+code2.size()+code3.size()); i++)
        {
            for (j = 0; j < use_end3.size(); j++)
            {
                if (i == use_end3[j]+fc2)
                {
                    for (k = 0; k < global_end.size(); k++)
                    {
                        if (use_label3[j] == global_label[k])
                        {
                            //use_end1[j] = global_end[k];
                            code_ligado[i] = code_ligado[i] + global_end[k] - fc2;
                        }
                    }
                }
            }
        }







    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////                                    ESCREVE CÓDIGO                                              ////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////


    



    arquivo_saida = arquivo_entrada1.substr(0, arquivo_entrada1.size() - 2);

    std::ofstream writefile (arquivo_saida.c_str());

    //std::cout << "\nRelatives:"<< std::endl;
    
    writefile << "Name:\n";
    writefile << arquivo_saida<< "\n";
    writefile << "Size:\n";
    writefile << code_ligado.size() << "\n";






    writefile << "Relatives:\n";

    for (i = 0; i < global_relative.size(); i++)
    {
            //std::cout << global_relative[i] << " ";
            writefile << global_relative[i] << " ";
    };


    //std::cout << "\nCode:" << std::endl;
    writefile << "\nCode:\n";




	for (i = 0; i< code_ligado.size(); i++)
    {


		if (0 > code_ligado[i] && code_ligado[i] > -9)
		{
			//std::cout << "-0" << abs(code_ligado[i])<< " ";
			writefile << "-0" << abs(code_ligado[i])<< " ";
		}
		else if (0 <= code_ligado[i] && code_ligado[i] < 10)
		{
			//std::cout << "0" << code_ligado[i]<< " ";
			writefile << "0" << code_ligado[i]<< " ";

		}
		else{
			//std::cout <<code_ligado[i]<< " " ;
			writefile  << code_ligado[i]<< " ";
		}
    }



    //for (i=0; i<global_relative.size();i++)
    //   std::cout<<global_relative[i]<<std::endl;
	

    return 0;

}
