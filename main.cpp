#include "bridgesim.h"

void print_bridge(vector<bridge> &b)
{
  for(int i=0;i<b.size();i++)
  {
    cout<<b[i].own_ID<<": ";
    for(int j=0;j<b[i].LAN.size();j++)
    {
      cout<<b[i].LAN[j].ID<<"-"<<b[i].LAN[j].status<<" ";
    }
    cout<<endl;
  }
}

void simulate(vector<bridge> &b,int n_bridges, int trace_flag)
{
  int t=0;
  bool change = true;
  while(change)
  {
    change=false;
    t++;
    for(int i=0;i<n_bridges;i++)
    {
      if(b[i].forward==true)
        {
          b[i].send_config(b,t,trace_flag);
        }
    }
    for(int i=0;i<n_bridges;i++)
    {
      if(b[i].check_config(t,trace_flag))
      {
        change=true;
      }
    }
  }
}

bool compare(LAN_of_bridge a, LAN_of_bridge b)
{
	if(a.ID < b.ID)
		return 1;
	else
		return 0;
}

bool compare_table(table_entry a, table_entry b)
{
	if(a.host < b.host)
		return 1;
	else
		return 0;
}

int main() {
  int trace_flag, n_bridges;

  cin>>trace_flag;
  cin>>n_bridges;
  vector<bridge> b (n_bridges);
  string s;
  getline(cin,s);
  for(int i=0;i<n_bridges;i++)
  {

    getline(cin,s);
    b[i].own_ID=s.substr(0,2);
    b[i].root_ID=b[i].own_ID;
    b[i].root_dist=0;
    b[i].sending_bridge=b[i].own_ID;
    for(int j=4;j<s.size();j+=2)
    {
      LAN_of_bridge temp;
      temp.ID= s.substr(j,1);
      temp.root_dist=0;
      temp.status="DP";
      b[i].LAN.push_back(temp);
    }
  }
  for(int i=0;i<n_bridges;i++)
  {
    sort(b[i].LAN.begin(), b[i].LAN.end(),compare);
  }

simulate(b,n_bridges,trace_flag);
print_bridge(b);




//adding hosts and using the spanned tree
//vector<independent_LAN> LAN;
int n_LANs=count_LANs(b);


for(int i=0;i<n_LANs;i++)
{
  string str;
  getline(cin,str);
  vector<string> host;
  string input;
    stringstream iss(str);
    iss>>input;
    host.push_back(input);
    while(iss>>input)
       {
          host.push_back(input);
       }
    for(int i=0;i<b.size();i++)
   {
    for(int j=0;j<b[i].LAN.size();j++)
    {
      if(b[i].LAN[j].status=="NP")
      {
        continue;
      }
      if(host[0][0]==b[i].LAN[j].ID[0])
      {
        for(int k=1;k<host.size();k++)
        {
          b[i].LAN[j].hosts.push_back(host[k]);
        }
      }
    }
   }

}
 
int n_transfer;
cin>>n_transfer;
string sender, receiver;
for(int i=0;i<n_transfer;i++)
{
  string sending_bridge= "NULL";
  cin>>sender>>receiver;
  int time=0;
  bool found=false;
  for(int i=0;i<b.size();i++)
  {
    for(int j=0;j<b[i].LAN.size();j++)
    {
      if(b[i].LAN[j].status!="NP")
      {
        for(int k=0;k<b[i].LAN[j].hosts.size();k++)
        {
          if(b[i].LAN[j].hosts[k]==sender)
          {
            transfer_packet(sender,receiver,b,time,sending_bridge,&b[i].LAN[j]);

            for(int i=0;i<n_bridges;i++)
           {
             sort(b[i].forwarding_table.begin(), b[i].forwarding_table.end(),compare_table);
           }
            
            for(int i=0;i<b.size();i++)
		      	{
              cout<<b[i].own_ID<<":"<<endl;
              cout<<"HOST ID | FORWARDING PORT"<<endl;
              for(int j=0;j<b[i].forwarding_table.size();j++)
              {
                          cout<<b[i].forwarding_table[j].host<<" | "<<b[i].forwarding_table[j].LAN->ID<<endl;
              }
             }

            found=true;
            break;
          }
          if(found==true)
          {
            break;
          }
          
        }
      if(found==true)
          {
            break;
          }
      }
    }
    if(found==true)
          {
            break;
          }
  } 
}


cout<<"successfully executed";
}


