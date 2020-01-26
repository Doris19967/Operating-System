/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package os;

/**
 *
 * @author Administrator
 */
public class Create {
    public Node createNode(Node head, String name, int priority, int runtime, int arrivaltime, int starttime, int endtime, int turntime, double dturntime){

	        if(head == null){
	            Node node = new Node(name,priority,runtime,arrivaltime,starttime,endtime,turntime,dturntime);
	            head = node;
	            return head;
	        }
	        Node cur = head;
	        while(cur.nextnode!=null){
	            cur = cur.nextnode;
	        }
	        Node node = new Node(name,priority,runtime,arrivaltime,starttime,endtime,turntime,dturntime);
	        cur.nextnode = node;
	        return head;
	    }

	    public void check(Node head){
	        if(head == null){
	            System.out.println("当前队列为空！");
	            return;
	        }
	        Node cur = head;
	        while(cur!=null){
	            System.out.println("进程名:"+cur.name+"\t优先级:"+cur.priority+"\t运行时间:"+cur.runtime+"\t到达时间:"+cur.arrivaltime);
	            cur = cur.nextnode;
	        }
	    }
}
