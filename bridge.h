#include<iostream>
#include<bits/stdc++.h>
using namespace std;


struct LAN_of_bridge// LANs connected to a bridge
{
  public:
  string ID;
  int root_dist;
  vector<string> hosts;
  string status; //NP, RP, DP; when taking with respect to a bridge;

};

struct configuration_received
{
  string sender;
  int root_dist;
  string root;
  LAN_of_bridge* receiving_LAN=NULL;
};
struct table_entry{
  string host;
  LAN_of_bridge *LAN;
};
class bridge
{
  public:
  int root_dist;
  string root_ID;
  string own_ID;
  string sending_bridge;
  bool forward =true;
  vector<LAN_of_bridge> LAN; //LANs connected to the bridge
  vector<configuration_received> config;//configuration messages received
  vector<table_entry> forwarding_table;
  void add_config(string x, int y, string z,LAN_of_bridge &LAN)
  {
    configuration_received new_config;
    new_config.root=x;
    new_config.root_dist=y;
    new_config.sender=z;
    new_config.receiving_LAN= &LAN;
    config.push_back(new_config);
  }
void send_config(vector<bridge> &b, int t,int trace_flag)
{
  for(int i=0;i<LAN.size();i++)
  {

    if(LAN[i].status=="NP"||LAN[i].status=="RP")
    {
      continue;
    }
    if(root_ID==own_ID&&trace_flag==1)
      {
        cout<<t-1<<" s "<<own_ID<<" ("<<root_ID<<", "<<root_dist<<", "<<own_ID<<")\n";
      }
    for(int j=0;j<b.size();j++)
    {
      if(b[j].own_ID==own_ID)
        {
          continue;
        }
      for(int k=0;k<b[j].LAN.size();k++)
      {
        if(b[j].LAN[k].ID==LAN[i].ID)
        {
          b[j].add_config(root_ID, root_dist,own_ID,b[j].LAN[k]);
        }
      }
    }

  }
  if(own_ID!=root_ID)
  {
    forward=false;
  }
  return;
}
void change_config(int i)
{
  root_ID=config[i].root;
  root_dist=config[i].root_dist+1;
  config[i].receiving_LAN->status="RP";
  string changed = config[i].receiving_LAN->ID;
  config[i].receiving_LAN->root_dist=config[i].root_dist;
  sending_bridge=config[i].sender;
  for(int i=0;i<LAN.size();i++)
  {
    if(LAN[i].status=="RP"&&LAN[i].ID!=changed)
    {
      LAN[i].status="NP";
    }
  }

  forward=true;
}
bool check_config(int t, int trace_flag)
{
  bool change=false;
  for(int i=0;i<config.size();i++)
  {
    if(trace_flag==1)
    {
      cout<<t<<" r "<<own_ID<<" ("<<config[i].root<<", "<<config[i].root_dist<<", "<<config[i].sender<<")\n";
    }
      if(config[i].root<root_ID)
      {
        change_config(i);
        change= true;
        continue;
      }
      else if(config[i].root==root_ID)
      {
        if(config[i].root_dist+1<root_dist)
       {
          change_config(i);
          change= true;
          continue;
       }
       else if(config[i].root_dist+1==root_dist)
       {
         if(config[i].sender<sending_bridge)
         {
           change_config(i);
           change=true;
           continue;
         }
       }
      }
      if(config[i].root==root_ID&&config[i].root_dist<root_dist)
      {

        if(config[i].receiving_LAN->status=="DP")
        {
          config[i].receiving_LAN->root_dist=config[i].root_dist;
          config[i].receiving_LAN->status="NP";
          change= true;
        }

        continue;
      }
      else if(config[i].root==root_ID&&config[i].root_dist==root_dist&&config[i].sender<own_ID)
      {
        if(config[i].receiving_LAN->status=="DP")
        {
          config[i].receiving_LAN->status="NP";
          change=true;
        }

        continue;
      }
  }
  config.clear();
  return change;
}
};
