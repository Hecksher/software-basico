
/*  CARREGADOR
 *  Cristiana Miranda de Farias - 10/0129323
 *  Pedro Henrique Hecksher Faber - 10/0119140
 */



#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

int main(int argc, char * argv[])
{

    int num;
    int i = 0, pc =0, acc = 0;
    bool stop = false;
    std::string arquivo_saida;
    std::vector<int> obj;
    std::vector<int> rel;


    //////////////////////////////////////////////////////////////////
    ////						GET RELATIVES				      ////
    //////////////////////////////////////////////////////////////////



    std::fstream relative(argv[1], std::ios_base::in);
    relative.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    relative.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    relative.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    relative.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    relative.ignore(std::numeric_limits<std::streamsize>::max(),'\n');    
    
    while (relative >> num)
    {
        rel.push_back(num);
    }


	//////////////////////////////////////////////////////////////////
    ////						 GET CODE					      ////
    //////////////////////////////////////////////////////////////////



    std::fstream code(argv[1], std::ios_base::in);
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    code.ignore(std::numeric_limits<std::streamsize>::max(),'\n');



    while (code >> num)
    {
        obj.push_back(num);
    }


    while ( stop == false )
    {
    	

    	switch (obj[pc])
        {
            case 0x1:
		    	//std::cout << "ADD " << obj[obj[pc+1]] << std::endl;
		    	acc = acc + obj[obj[pc+1]];
   		    	pc += 2;
                break;

            case 0x2:
		    	//std::cout << "SUB " << obj[obj[pc+1]] << std::endl;
		    	acc = acc - obj[obj[pc+1]];
   		    	pc += 2;
   		    	//std::cout << "Resultado " << acc << std::endl;

                break;

            case 0x3:
   		    	//std::cout << "MUL " << obj[obj[pc+1]] << std::endl;
   		    	acc = acc*obj[obj[pc+1]];
   		    	//std::cout << "Resultado " << acc << std::endl;

   		    	pc += 2;
                break;

            case 0x4:
   		    	//std::cout << "DIV " << obj[obj[pc+1]] << std::endl;
   		    	if ( obj[obj[pc+1]] == 0 )
   		    	{
   		    		std::cout << "Erro: divisão por zero." << std::endl;
   		    		stop = true;
   		    	}
   		    	else
   		    	{
   		    		acc = acc/obj[obj[pc+1]];
   		    		//std::cout << "Resultado " << acc << std::endl;
   		    		pc += 2;
  		    	}
                break;

            case 0x5:
   		    	//std::cout << "JMP " << obj[pc+1] << std::endl;
   		    	pc=obj[pc+1];
                break;

            case 0x6:
   		    	//std::cout << "JMPN " << obj[pc+1] << std::endl;
   		    	if (acc<0)
   		    		pc=obj[pc+1];
   		    	else
   		    		pc += 2;
                break;

            case 0x7:
   		    	//std::cout << "JMPP " << obj[pc+1] << " " << acc << std::endl;
   		    	if ( acc > 0){ 
   		    		pc=obj[pc+1];
   		    		   		    		//stop = true;
   		    	}
   		    	else
   		    		pc += 2;
                break;

            case 0x8:
   		    	if (acc==0){
   		    		//std::cout << "JMPZ " << obj[pc+1] << std::endl;

   		    		pc=obj[pc+1];
   		    	}
   		    	else
   		    		pc += 2;
                break;

            case 0x9:
   		    	//std::cout << "COPY " << obj[obj[pc+1]] << " em " << obj[obj[pc+2]] << std::endl;
   		    	obj[obj[pc+2]] = obj[obj[pc+1]];
   		    	pc += 3;
                break;

            case 0xA:
                //std::cout << "LOAD " << obj[obj[pc+1]] << std::endl;
                acc = obj[obj[pc+1]];
                pc += 2;

                break;

            case 0xB:
                //std::cout << "STORE " << obj[obj[pc+1]] << std::endl;
                obj[obj[pc+1]] = acc;
                pc += 2;
                break;

            case 0xC:
                std::cout << "INPUT: ";
                std::cin >> obj[obj[pc+1]];
                pc += 2;

                break;

            case 0xD:
                std::cout << "OUTPUT: " << obj[obj[pc+1]] << std::endl;

                pc += 2;
                break;

            case 0xE:
                
                stop = true;

                break;

            default:
                std::cout << "Programa sem STOP." << std::endl;
                stop= true;
                break;
        }


    }


    arquivo_saida = argv[1];
    arquivo_saida = arquivo_saida + ".im";
    

    std::ofstream writefile (arquivo_saida.c_str());

    for (i=0; i < obj.size(); i++)
    {
    	writefile << obj[i]<< " ";    	
    }

    //std::cout << arquivo_saida << std::endl;

    return 0;

}
