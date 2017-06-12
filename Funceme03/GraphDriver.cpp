#include "graphdriver.h"

GraphDriver::GraphDriver(int graphSize, std::vector<Edge> edges)
{
	m_graph = Graph(graphSize);
	buildAdjList(edges);
}

GraphDriver::~GraphDriver()
{
}

void GraphDriver::buildAdjList(std::vector<Edge> edges)
{
	for (auto e : edges)
	{
		auto src = e.getSrc();
		auto dest = e.getDest();

		auto adjList = m_graph.getAdjList();
		adjList[src->getId()].push_back(dest);
	}
}

void GraphDriver::printGraph()
{
	for (auto i = 0; i < m_graph.getNumVertices(); i++)
	{
		if (m_graph.getAdjList()[i].empty())
		{
			continue;
		}

		std::cout << i << " --> ";

		for (auto v : m_graph.getAdjList()[i])
		{
			std::cout << v->getId() << " (" << &(*v) << ") ";
		}
		std::cout << std::endl;
	}
}

bool GraphDriver::reachingClients(int step, Vertex* provider, float* clientsRequest)
{
	auto provNeighbors = m_graph.getNeighbors(provider);
	auto stepFurther = false;

	for (auto neighVertex : provNeighbors)
	{
		//When the neighbor is a client
		if (Type::CLIENT == neighVertex->getType())
		{
			if (neighVertex->getValue() <= provider->getValue())
			{
				stepFurther = true;
				std::cout << "F(" << step << ") = " << provider->getValue() << '\n'
					<< "F libera " << neighVertex->getValue() << " para C" << neighVertex->getId() << '\n';

				provider->setValue(provider->getValue() - neighVertex->getValue());
				*clientsRequest += neighVertex->getValue();
			}
			else
			{
				std::cout << "F(" << step << ") = " << provider->getValue() << '\n'
					<< "F nao consegue mais liberar para C" << neighVertex->getId() << '\n';
			}
		}
		//When the neighbor is a joint
		else if (Type::JOINT == neighVertex->getType())
		{
			auto clientsRequest = 0.0f;
			neighVertex->setValue(provider->getValue());
			reachingClients(step, neighVertex, &clientsRequest);
			provider->setValue(provider->getValue() - clientsRequest);
		}
	}

	return stepFurther;
}


bool GraphDriver::stepExecution(int step, Vertex* provider)
{
	auto stepFurther = false;

	std::cout << "\nPasso " << step << '\n'
		<< "=======\n";

	auto clientsRequest = 0.0f;
	stepFurther = reachingClients(step, provider, &clientsRequest);

	return stepFurther;
}

void GraphDriver::run(Vertex* provider)
{
	auto step = 1;

	while (stepExecution(step++, provider)) {}
}














