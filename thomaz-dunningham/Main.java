import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();

        while (T-- > 0) {
            int nVertices = scanner.nextInt();
            int nArestas = scanner.nextInt();
            Grafo grafo = new Grafo(nVertices);
            grafo.insereArestaPeso(scanner, nArestas);
            int inicio = scanner.nextInt();
            int fim = scanner.nextInt();
            grafo.djikistra(inicio-1, fim-1);
        }
    }

    
    private static class Pair {
        public int aresta, peso;
        
        Pair(int aresta, int peso) {
            this.aresta = aresta;
            this.peso = peso;
        }
    }

    private static class Grafo {
        int vertices;
        List<List<Pair>> adjList;
        
        Grafo(int vertices) {
            this.vertices = vertices;
            this.adjList = new ArrayList<>();
            for (int i = 0; i < vertices; i++) {
                adjList.add(new ArrayList<>());
            }
        }
        
        void insereArestaPeso(Scanner scanner, int nArestas) {
            int orig, dest, peso;
            for (int i = 0; i < nArestas; i++) {
                orig = scanner.nextInt();
                dest = scanner.nextInt();
                peso = scanner.nextInt();
                adjList.get(orig-1).add(new Pair(dest-1, peso));
                adjList.get(dest-1).add(new Pair(orig-1, peso));
            }
        }

        void djikistra(int inicio, int fim) {
            Queue<Pair> queue = new PriorityQueue<>(Comparator.comparingInt(pair -> pair.peso));
            int[] distancias = new int[vertices];
            Arrays.fill(distancias, Integer.MAX_VALUE);

            distancias[inicio] = 0;
            queue.add(new Pair(inicio, 0));

            while (!queue.isEmpty()) {
                Pair atual = queue.poll();

                for (Pair visinho : adjList.get(atual.aresta)) {
                    if (distancias[visinho.aresta] > atual.peso + visinho.peso) {
                        distancias[visinho.aresta] = atual.peso + visinho.peso;
                        queue.add(new Pair(visinho.aresta, visinho.peso));
                    }
                }
            }

            if (distancias[fim] != Integer.MAX_VALUE) {
                System.out.println(distancias[fim]);
            } else {
                System.out.println("NO");
            }
        }
    }
}