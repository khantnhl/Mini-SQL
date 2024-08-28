#ifndef SHUNTINGYARD_CPP
#define SHUNTINGYARD_CPP

#include "shuntingyard.h"

Shunting_yard::Shunting_yard(){};

// Convert vector string -> token queue
Shunting_yard::Shunting_yard(const vectorstr& infix_strings)
{
    for(int i = 0; i < infix_strings.size(); i++)
    {
        if(infix_strings[i] == "("){ _infix_tqueue.push(new LParen("(") ); }
        else if(infix_strings[i] == "<" || infix_strings[i] == ">" || infix_strings[i]== "<=" || infix_strings[i] == ">=" || infix_strings[i]== "="){ _infix_tqueue.push(new Relational(infix_strings[i])); }
        else if(infix_strings[i] == "and" || infix_strings[i] == "or"){ _infix_tqueue.push(new Logical(infix_strings[i])); }
        else if (infix_strings[i] == ")"){ _infix_tqueue.push(new RParen(")")); }
        else {
            _infix_tqueue.push(new TokenStr(infix_strings[i]));
        }
    }

}

//Work Flow
// take in infix queue -> post_fix queue
Queue<Token*> Shunting_yard::postfix()
{

    Stack<Token*> stack;

    while(!_infix_tqueue.empty())
    {
        Token* hold = _infix_tqueue.front();

        switch(hold->get_token_type())
        {
            case TOKENSTR:
                _postfix_tqueue.push(_infix_tqueue.pop());
                break;

            case LPAREN:
                stack.push(_infix_tqueue.pop());
                break;

            case RPAREN: 
                _infix_tqueue.pop();

                while(!stack.empty() && stack.top()->get_token_type() != LPAREN) //if you see RPAREN pop till LPAREN
                {
                    _postfix_tqueue.push(stack.pop());
                    if(stack.empty())
                    {
                        //poping indefinite
                        throw std::runtime_error("Parenthesis imbalance. Missing LPAREN. ");
                    }
                }

                if(!stack.empty()){
                    stack.pop(); //cleared last one "("
                }
                break;

            case RELATIONAL:


                while(!stack.empty() && stack.top()->get_token_type() == RELATIONAL) //if RELATIONAL, check stack top 
                { 
                    _postfix_tqueue.push(stack.pop());
                }

                stack.push(_infix_tqueue.pop());

                break;

            case LOGICAL:
            
                if(hold->get_token_str() == "or") 
                {
                    if(stack.empty()){
                        stack.push(_infix_tqueue.pop()); //when stack empty
                        break;
                    } 

                    //if holding or -> empty out the stack until LPAREN
                    //because "or" has the lower precedence 
                    //cannot stay operators other than a left parenthesis
                    while(!stack.empty())
                    {
                        if(stack.top()->get_token_type() == LPAREN){ break; }

                        _postfix_tqueue.push(stack.pop());
                    }

                    stack.push(_infix_tqueue.pop());
                    break;
                }
                else if (hold->get_token_str() == "and")
                {
                    if(stack.empty()){
                        stack.push(_infix_tqueue.pop());
                        break;
                    } 

                    //"and has higher precedence so stop poping when we found "or" or a lparen
                    // so we can maintain groupings
                    while(!stack.empty() && stack.top()->get_token_str() != "or")
                    {   
                        if(stack.top()->get_token_type() == LPAREN){ break; }

                        _postfix_tqueue.push(stack.pop());

                    }
                        
                    stack.push(_infix_tqueue.pop()); // 'and' on top of 'or'
                    break;
                }
                
            default: 
                throw std::runtime_error("Error : " + hold->get_token_str());
                break;
            }
    }
    

    //empty out stack at the end and push to queue
    while(!stack.empty())
    {
        if (stack.top()->get_token_type() == LPAREN)
        {
            throw std::runtime_error("Parenthesis imbalance. Missing RPAREN. ");
        }
        _postfix_tqueue.push(stack.pop());

    }


    if(!stack.empty() && !_infix_tqueue.empty())
    {
        throw std::runtime_error("Shunting Yard Error\n");
    }
            
    cout<< _postfix_tqueue <<endl;

    return _postfix_tqueue;
}

#endif