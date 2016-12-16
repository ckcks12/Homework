/**
 * Created by ckcks12 on 2016. 12. 14..
 */

import java.util.*;
import java.math.*;
import java.util.concurrent.Callable;

public class Main {
    static class Person implements Cloneable{
        int dist = 0;
        int cmp_cnt = 0;
        boolean done = false;
        LinkedList<Integer> trace = new LinkedList<>();
        public boolean isVisited(int idx)
        {
            for(int i : trace)
            {
                if( i == idx )
                    return true;
            }
            return false;
        }
        public void visit(int idx, int dist)
        {
            trace.push(idx);
            this.dist += dist;
        }
        public boolean isVisitedAll(int max)
        {
            for(int i=0; i<max; i++ )
            {
                if( ! isVisited(i) )
                    return false;
            }
            return true;
        }
        public int getDepth()
        {
            return trace.size() - 1;
        }
        @Override
        protected Person clone() {
            try {
                Person person = (Person)super.clone();
                person.trace = (LinkedList)trace.clone();
                return person;
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
                return null;
            }
        }
    }

    public static void main(String[] args) {
        int[][] graph = {};
        int[][] graph5 = {
                {0, 1, 3, 5, 4},
                {3, 0, 4, 7, 7},
                {6, 4, 0, 4, 8},
                {1, 2, 3, 0, 4},
                {7, 3, 2, 4, 0}
        };
        int[][] graph10 = {

        };



        Scanner scanner = new Scanner(System.in);
//        int select = scanner.nextInt();
        int select = 5;

        if( select == 5 )
        {
            graph = graph5;
        }
        else if( select == 10 )
        {
            graph = graph10;
        }
        else
        {
            System.out.println("how there you");
        }

        System.out.println("1. Breath First Search");
        System.out.println("2. Best - Textbook Version");
        System.out.println("3. Best - Estimated Version");
        System.out.println("4. Best - Kown Cost Version");
//        select = scanner.nextInt();
        select = 1;

        algorithm(graph, select);
    }

    public static void algorithm(int[][] graph, int bound_type)
    {
        int cmp_cnt = 0;
        LinkedList<Person> queue = new LinkedList<>();
        Person done = null;
        Person person = null;

        // first start queue
        person = new Person();
        person.visit(0, 0);
        queue.offer(person.clone());

        while(!queue.isEmpty())
        {
            cmp_cnt++;

            // 큐에서 꺼내기 전에 bound 친다

            // 큐에서 하나 꺼낸다
            // 이때 알고리즘 타입에 따라 다르게 꺼낸다
//            person = queue.poll();
            switch(bound_type)
            {
                case 1:
                    person = queue.poll();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    HashMap<Integer, Integer> map = new HashMap<>();
                    int max_depth = 0;
                    for(Person p : queue)
                    {
                        if( p.getDepth() > max_depth )
                            max_depth = p.getDepth();

                        if( ! map.containsKey(p.getDepth()) )
                        {
                            map.put(p.getDepth(), p.dist);
                        }
                        else
                        {
                            if( map.get(p.getDepth()) > p.dist )
                                map.put(p.getDepth(), p.dist);
                        }
                    }

                    break;
            }

            // 모든 곳 다 갔었으면 이제 0으로 빡구하면서 done이랑 비교해본다.
            if( person.isVisitedAll(graph.length) )
            {
                person.visit(0, graph[person.trace.getLast()][0]);
                if( done == null )
                {
                    person.cmp_cnt = cmp_cnt;
                    done = person;
                }
                else
                {
                    if( done.dist > person.dist )
                    {
                        person.cmp_cnt = cmp_cnt;
                        done = person;
                    }
                }
            }
            // 아니라면 갈 수 있는 모든 곳으로 간다
            else
            {
                for(int i=0; i<graph.length; i++ )
                {
                    if( graph[person.trace.getLast()][i] > 0  && ! person.isVisited(i) )
                    {
                        Person p = person.clone();
                        p.visit(i, graph[person.trace.getLast()][i]);
                        queue.offer(p);
                    }
                }
            }

        }

        if( done != null )
        {
            System.out.println("trace");
            for(int i : done.trace)
            {
                System.out.print(i);
                System.out.print("->");
            }
            System.out.println("");
            System.out.println("compare count : " + String.valueOf(done.cmp_cnt));
//            System.out.println("compare count : " + String.valueOf(cmp_cnt));
        }
    }
}
