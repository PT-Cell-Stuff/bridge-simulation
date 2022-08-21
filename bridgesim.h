#include "bridge.h"


int count_LANs(vector<bridge> &b)
{
  vector<string> LAN;
  for(int i=0;i<b.size();i++)
  {
    for(int j=0;j<b[i].LAN.size();j++)
    {
      if(b[i].LAN[j].status=="NP")
      {
        continue;
      }
      bool found=false;
      for(int k=0;k<LAN.size();k++)
      {
        if(b[i].LAN[j].ID==LAN[k])
        {
          found=true;
        }
      }
      if(!found)
      {
        LAN.push_back(b[i].LAN[j].ID);
      }
     
    }
  }
   return LAN.size();
}



void transfer_packet(string sender, string receiver,vector<bridge> &b,int time, string sending_ID, LAN_of_bridge *LAN)
{
  for(int i=0;i<b.size();i++)
  {
    if(b[i].own_ID==sending_ID)
    {
      continue;
    }
    for(int j=0;j<b[i].LAN.size();j++)
    {
      if(b[i].LAN[j].ID==LAN->ID&&b[i].LAN[j].status!="NP")
      {
          bool found=false, sent=false;

           for(int k=0;k<b[i].forwarding_table.size();k++)
           {

              if(b[i].forwarding_table[k].host==sender)
              {
               found=true;
              }
              if(b[i].forwarding_table[k].host==receiver)
             {

                time++;
                sent=true;
                if((b[i].forwarding_table[k].LAN->ID!=LAN->ID))
                {
                cout<<time<<" s "<<b[i].own_ID<<" "<<LAN->ID<<"--"<<b[i].forwarding_table[k].LAN->ID<<endl;

               transfer_packet(sender,receiver,b,time,b[i].own_ID,b[i].forwarding_table[k].LAN);
                }
              }
           }
            
        
      if(!found)
      {
        table_entry temp;
        temp.host= sender;
        temp.LAN=&b[i].LAN[j];
        b[i].forwarding_table.push_back(temp);
      }
      if(!sent)
      {
        for(int m=0; m<b[i].LAN.size(); m++)
        {
          if((b[i].LAN[m].ID !=LAN->ID)&&(b[i].LAN[m].status !="NP"))
          {
            time++;
             cout<<time<<" s "<<b[i].own_ID<<" "<<LAN->ID<<"--"<<b[i].LAN[m].ID<<endl;

           transfer_packet(sender,receiver,b,time,b[i].own_ID,&b[i].LAN[m]);
          }

        }
      }

      }
      }
    }
  }


  


    


