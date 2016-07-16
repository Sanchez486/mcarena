//start choosing process

void chooseHeroes(HeroVector *heroes)
{
	int money = playerCPU->getCurrentMoney();
	int i = 0;
	int avCost = heroes.getAvarageCost();
	int avHp = heroes.getAvarageHp();
	
	// trying to get a tank
	
	sort (heroes.begin(), heroes.end(), sort_by_hp); //max at the beginning
	i = getRandom(heroes.size()/6-heroes.size()%6,heroes.size()/4-heroes.size()%4);
	sort (heroes.begin(), heroes.at(i), sort_by_cost); //max at the beginning
	if(heroes.at(i).getStats.cost < avCost + getRandom((avCost/4-avCost%4),(avCost/3-avCost%3))) //how much CPU is able to pay for this hero
	   playerCPU->getHeroGroup.set(front1,heroes.at(i));
	else playerCPU->getHeroGroup.set(front1,heroes.at(i + getRandom(1,4))); // Ok, let's try another...
	money -= playerCPU->getHeroGroup.at(front1).getStats.cost;
	HeroPosition lastAdded = HeroPosition::front1;
	moneyCheck(money); // check if had the CPU enought money or not
	
	//trying to get a support
	
	sort (heroes.begin(), heroes.end(), sort_back_by_hp); //min at the beginning
	i = 0;
	while(heroes.at(i).hp >= heroes.begin().hp + getRandom((int)(avHp/6-avHp%6),(int)(avHp/3-avHp%3))) i++;	
	sort (heroes.begin(), heroes.at(i), sort_by_cost);
	for(int j = 0; j < i; j++)
	{
		if((heroes.at(j).getStats.skill.getName = "heal" || 
		   heroes.at(j).getStats.skill.getName = "anti-effects" 
		   /* || some else support skills*/ )
		  && heroes.at(j).getStats.cost < 
		   avCost + getRandom((avCost/4-avCost%4),avCost))
		{
			playerCPU->getHeroGroup.set(back1, heroes.at(j));
			break;
		}
	}
	if (!playerCPU->getHeroGroup.at(back1)) // if position is empty
		playerCPU->getHeroGroup.set(back1, heroes.at(j+getRandom(1,3))); // Ok, let's get someone other
	money -= playerCPU->getHeroGroup.at(back1).getStats.cost;
	lastAdded = HeroPosition::back1;
	moneyCheck(money);
	
	// trying to get DD
	
	sort (heroes.begin(), heroes.end(), sort_by_damage); //max at the beginning
	i = getRandom(heroes.size()/6-heroes.size()%6,heroes.size()/4-heroes.size()%4);
	sort (heroes.begin(), heroes.at(i), sort_by_cost);
	for(int j = 0; j < i; j++)
	{
		if(heroes.at(j).getStats.cost < 
		   avCost + getRandom((avCost/4-avCost%4),(avCost/3-avCost%3)))
		{
			if(heroes.at(j)->getStats.kind = Kind::melee)
			{
				playerCPU->getHeroGroup.set(front2, heroes.at(j));
				lastAdded = HeroPosition::front2;
			}
			else
			{
				playerCPU->getHeroGroup.set(back2, heroes.at(j));
				lastAdded = HeroPosition::back2;
			}
			break;
		}
	}	
	
	if(!playerCPU->getHeroGroup.at(front2) && !playerCPU->getHeroGroup.at(back2)) //Ok...
	{
		j += getRandom(1,3);
		if(heroes.at(j)->getStats.kind = Kind::melee)
		{
			playerCPU->getHeroGroup.set(front2, heroes.at(j));
			lastAdded = HeroPosition::front2;
		else
		{
			playerCPU->getHeroGroup.set(back2, heroes.at(j));
			lastAdded = HeroPosition::back2;
		}
	}
	money -= heroes.at(j)->getStats.cost;
	moneyCheck(money);
	
	// trying to get some hero with big init
	
	sort (heroes.begin(), heroes.end(), sort_by_init); //max at the beginning
	i = getRandom(heroes.size()/6-heroes.size()%6,heroes.size()/4-heroes.size()%4);
	sort (heroes.begin(), heroes.at(i), sort_by_cost);
	for(int j = 0; j < i; j++)
	{
		if(heroes.at(j).getStats.cost < 
		   avCost + getRandom((avCost/4-avCost%4),(avCost/3-avCost%3)))
		{
			if(!playerCPU->getHeroGroup.at(front2))
			{
				playerCPU->getHeroGroup.set(front2, heroes.at(j));
				lastAdded = HeroPosition::front2;
			else
			{
				playerCPU->getHeroGroup.set(back2, heroes.at(j));
				lastAdded = HeroPosition::back2;	
			}
			break;
		}
	}					
	
	
	if(!playerCPU->getHeroGroup.at(front2) || !playerCPU->getHeroGroup.at(back2))
	{
		j += getRandom(1,3);
		if(!playerCPU->getHeroGroup.at(front2))
		{
			playerCPU->getHeroGroup.set(front2, heroes.at(j));
			lastAdded = HeroPosition::front2;
		}
		else
		{
			playerCPU->getHeroGroup.set(back2, heroes.at(j));
			lastAdded = HeroPosition::back2;
		}
	}
	money -= heroes.at(j)->getStats.cost;
	moneyCheck(money);
	
	// trying to get some common hero
	
	sort (heroes.begin(), heroes.end(), sort_by_init);
	i = getRandom(-1,2);
	sort (heroes.at(heroes.size()/3-heroes.size%3 + i),
		  heroes.at(2*(heroes.size()/3-heroes.size()%3) + i), 
		  sort_by_damage);
	j = getRandom(0,1);
	if(heroes.at(heroes.size()/2-heroes.size()%2 + j)->getStats.kind == Kind::melee)
	{
		playerCPU->getHeroGroup.set(front3, heroes.at(heroes.size()/2-heroes.size()%2 + j));
		lastAdded = HeroPosition::front3;
	}
		
	else
	{
		playerCPU->getHeroGroup.set(back3, heroes.at(heroes.size()/2-heroes.size()%2 + j));
		lastAdded = HeroPosition::back3;
	}
		
	money -= heroes.at(heroes.size()/2-heroes.size()%2 + j)->getStats.cost;
	Kind kind3 = heroes.at(heroes.size()/2-heroes.size()%2 + j)->getStats.kind; // for choosing the next one
	moneyCheck(money);
	
	// trying to get hero which is enough cheep to get them and 
	//enough expensive to let the money give off
	
	sort (heroes.begin(), heroes.end(), sort_by_cost);
	i = 0;
	while (heroes.at(i)->getStats.cost > money) i++;
	while (heroes.at(i)->getStats.kind == kind3) i++;
	if (heroes.at(i)->getStats.kind == Kind::melee)
		playerCPU->getHeroGroup.set(front3, heroes.at(i));
		
	else playerCPU->getHeroGroup.set(back3, heroes.at(i));
	
	money -= heroes.at(i)->getStats.cost;

}


void moneyCheck(*int)
{
	if(money < 0)
	{
		int max = playerCPU->getHeroGroup.at(lastAdded)->getStats.cost;
		sort (heroes.begin(), heroes.end(), sort_by_cost);
		i = 0;
		while (heroes.at(i)->getStats.cost >= max + getRandom(1,3)) i++;
		while (heroes.at(i)->getStats.kind != 
			   playerCPU->getHeroGroup.at(lastAdded)->getStats.kind) i++;
		money += max;
		playerCPU->getHeroGroup.set(lastAdded, heroes.at(i));
		money -= heroes.at(i)->getStats.cost;
		moneyCheck(money);
	}
}
	
		
																			   
																			   
																			   
	