//Parses CSV string and returns the list of comma separated string
typedef enum
{
    Parse_State_Start,
    Parse_State_End,
    Parse_State_Start_Field,
    Parse_State_Process_Field,
    Parse_State_Process_Q_Field,
    Parse_State_End_Q_Field,
    Parse_State_Error
} Parse_State;


bool csv_seperate(const string& s, vector<string>& list)
{
    bool status = true;
    if (s.length() == 0) 
        return status;
    
    size_t i = 0;
    string field;
    bool process = true;
    Parse_State cur_state = Parse_State_Start;

    while (process)
    {
        switch (cur_state)
        {
        case Parse_State_Start:
            assert(i == 0);
            cur_state = Parse_State_Start_Field;
            break;

        case Parse_State_Start_Field:
            if (i == s.length())
            {
                cur_state = Parse_State_End;
            }
            else if (s[i] == ',')
            {
                if (field.length() > 0)
                {
                    list.push_back(field);
                    field.clear();
                }
                ++i;
                //cur_state will remain the same
            }
            else if (s[i] == '\"')
            {
                ++i;
                cur_state = Parse_State_Process_Q_Field;
            }
            else
            {
                cur_state = Parse_State_Process_Field;
            }
            break;

        case Parse_State_Process_Field:
            if (i == s.length())
            {
                cur_state = Parse_State_End;
            }
            else if (s[i] == ',')
            {
                cur_state = Parse_State_Start_Field;
            }
            else
            {
                field += s[i];
                ++i;
            }
            break;

        case Parse_State_Process_Q_Field:

            if (i == s.length())
            {
                cur_state = Parse_State_End;
            }
            else if (s[i] == '\"')
            {
                ++i;
                cur_state = Parse_State_End_Q_Field;
            }
            else
            {
                field += s[i];
                ++i;
            }
            break;
            
        case Parse_State_End_Q_Field:
            if (i == s.length())
            {
                cur_state = Parse_State_End;
            }
            else if (s[i] == ',')
            {
                cur_state = Parse_State_Start_Field;
            }
            else
            {
                cur_state = Parse_State_Error;
            }

            break;
        
        case Parse_State_Error:
            status = false;
            process = false;
            break;

        case Parse_State_End:
            if (field.length() > 0)
                list.push_back(field);
            
            status = true;
            process = false;
            break;

        default:
            assert(0);
            process = false;
        }
    }

    return status;
}
