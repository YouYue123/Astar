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
	/*�ѳ�ʼ����ӽ������б�*/ 
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
		openList.pop();//ȡ�������б���Fֵ��С�ĵ� 
         
		closeList.push_back(tempNode);//���������뵽�ر��б� 
		
		if(tempNode.netX == endNetX && tempNode.netY == endNetY)
		{ 
		    printf("�ҵ��յ�\n");
		    pathNode terminal = tempNode;
            printf("%d %d\n",terminal.netX,terminal.netY);
            while(terminal.parent!=NULL)
            {
                terminal = *terminal.parent;
                printf("%d %d\n",terminal.netX,terminal.netY);
            } 
            break;//�ҵ��յ������� 
		} 
        printf("\n���ڵ���%d %d\n",tempNode.netX,tempNode.netY);
	    for(i=-1;i<2;i++)
			for(j=-1;j<2;j++)//�����ڽӵ�
			{
                
				if(tempNode.netX+i >=0 && tempNode.netX +i <=4 && tempNode.netY + j >=0 && tempNode.netY+j <=4 
					&&naviMap[tempNode.netX+i][tempNode.netY+j])//���ƶ��ķ���
				{
                    printf("\n���ƶ����� %d %d\n",tempNode.netX+i,tempNode.netY+j); 
					bool check = false;
					for(list<pathNode>::iterator iter = closeList.begin();iter!=closeList.end();iter++)//�鿴�ر��б��Ƿ���
					{
						if(iter->netX == tempNode.netX+i && iter->netY == tempNode.netY+j)
						{
							check = true;
							printf("�õ��ڹر��б��У�����\n");
							break;
						}
					}
					if(!check)//����ڹر��б���û�м�鵽
					{
                         printf("�õ㲻�ڹر��б���\n");
						 bool findOpen = false;
						 pathNode findNode;
                          //�鿴�����б�
						 for(list<pathNode>::iterator iter = backOpenList.begin();iter!=backOpenList.end();iter++)
						 {
							 if(iter->netX == tempNode.netX+i && iter->netY == tempNode.netY+j)
							 {
								 findNode = *iter;
								 findOpen = true;
							     printf("�õ��ڿ����б���\n");
								 break;
							 }
						 }
						  //��������б���û�У�����F �����趨��parent ���뿪���б�
						  if(findOpen == false)
						  {
                              printf("�õ㲻�ڿ����б���\n");
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
							  printf("�¼���ĵ�%d %d:\nF:%f G:%f H: %f\n",node.netX,node.netY,node.F,node.G,node.H);
							  
							  openList.push(node);
							  backOpenList.push_back(node);
						  }
						  else//��������б��д���
						  {
							  double G;
							  if(abs(i)+abs(j) == 2)
								  G = tempNode.G +1.414;
							  else
								  G= tempNode.G +1;
							  if(G < findNode.G)
							  {
                                  printf("����·���߱ȽϺ��ʣ�����\n");
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
