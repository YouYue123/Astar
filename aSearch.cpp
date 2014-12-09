#include<iostream>
#include<queue>
#include<list>
using namespace std;
bool naviMap[5][5];
priority_queue<struct pathNode> openList;
list<struct pathNode> backOpenList;
list<struct pathNode> closeList;
struct pathNode
{
	int netX,netY;
	struct pathNode *parent;
	double F;
	double G;
	double H;
  friend bool operator< (pathNode a, pathNode b)
   {
	  return a.F > b.F;
   }
};
struct Point
{
	int x;
	int y;
};
void aSearch(Point start,Point end)
{
	bool findDest = false;
	int i,j;
	int startNetX = start.x;
	int startNetY = start.y;
	int endNetX = end.x;
	int endNetY = end.y;
	/*把初始点添加进开启列表*/ 
	pathNode startNode;
	
    startNode.parent = NULL;
	startNode.G = 0;
	startNode.H = abs(startNetX - endNetX) + abs(startNetY - endNetY);
	startNode.F = startNode.G + startNode.H;
	startNode.netX = start.x;
	startNode.netY = start.y;
	
    openList.push(startNode);
	backOpenList.push_back(startNode);

	while(!openList.empty())
	{
		pathNode tempNode = openList.top();
		openList.pop();//取出开启列表中F值最小的点 
         
		closeList.push_back(tempNode);//把这个点加入到关闭列表 
		
		if(tempNode.netX == endNetX && tempNode.netY == endNetY)
		{ 
		    printf("找到终点\n");
		    pathNode terminal = tempNode;
            printf("%d %d\n",terminal.netX,terminal.netY);
            while(terminal.parent!=NULL)
            {
                terminal = *terminal.parent;
                printf("%d %d\n",terminal.netX,terminal.netY);
            } 
            break;//找到终点则跳出 
		} 
        printf("\n现在点是%d %d\n",tempNode.netX,tempNode.netY);
	    for(i=-1;i<2;i++)
			for(j=-1;j<2;j++)//处理邻接点
			{
                
				if(tempNode.netX+i >=0 && tempNode.netX +i <=4 && tempNode.netY + j >=0 && tempNode.netY+j <=4 
					&&naviMap[tempNode.netX+i][tempNode.netY+j])//可移动的方格
				{
                    printf("\n可移动方格 %d %d\n",tempNode.netX+i,tempNode.netY+j); 
					bool check = false;
					for(list<pathNode>::iterator iter = closeList.begin();iter!=closeList.end();iter++)//查看关闭列表是否含有
					{
						if(iter->netX == tempNode.netX+i && iter->netY == tempNode.netY+j)
						{
							check = true;
							printf("该点在关闭列表中，跳过\n");
							break;
						}
					}
					if(!check)//如果在关闭列表中没有检查到
					{
                         printf("该点不在关闭列表中\n");
						 bool findOpen = false;
						 pathNode findNode;
                          //查看开启列表
						 for(list<pathNode>::iterator iter = backOpenList.begin();iter!=backOpenList.end();iter++)
						 {
							 if(iter->netX == tempNode.netX+i && iter->netY == tempNode.netY+j)
							 {
								 findNode = *iter;
								 findOpen = true;
							     printf("该点在开启列表中\n");
								 break;
							 }
						 }
						  //如果开启列表中没有，更新F 并且设定好parent 加入开启列表
						  if(findOpen == false)
						  {
                              printf("该点不在开启列表中\n");
							  struct pathNode node;
							  node.parent = &closeList.back();
							  node.netX = tempNode.netX + i ;
							  node.netY = tempNode.netY + j ;
						  
							  if(abs(i)+abs(j) == 2)
							  node.G = node.parent->G + 1.414;
							  else
							  node.G = node.parent->G + 1;
                                
							  node.H = abs(node.netX - endNetX) + abs(node.netY - endNetY);

							  node.F = node.G + node.H;
							  printf("新加入的点%d %d:\nF:%f G:%f H: %f\n",node.netX,node.netY,node.F,node.G,node.H);
							  
							  openList.push(node);
							  backOpenList.push_back(node);
						  }
						  else//如果开启列表中存在
						  {
							  double G;
							  if(abs(i)+abs(j) == 2)
								  G = tempNode.G +1.414;
							  else
								  G= tempNode.G +1;
							  if(G < findNode.G)
							  {
                                  printf("从新路径走比较合适，更新\n");
								  findNode.parent = &closeList.back();
								  findNode.G = G;
								  findNode.F = G+ findNode.H;
							  }
						  }
					}
				}
			}	
	}
	
}
int main()
{
     memset(naviMap,true,sizeof(naviMap));
     naviMap[2][1] = false;
     naviMap[2][2] = false;
     naviMap[2][3] = false;
     Point start,end;
     start.x = 0; start.y = 0;
     end.x = 4; end.y = 4;
     aSearch(start,end);
     system("pause");
}
