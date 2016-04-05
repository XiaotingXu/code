import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.*;

/**
 * @author  Xiaoting Xu
 * @version 1.0
 * @since   2016-03-28
 */

public class CreditCardClient {

	public static void main(String[] args) {
		
		Socket clientSocket;
		
		try {
			
			 /* step 1: connect to the server name: "localhost" port number: 9141 */
			clientSocket = new Socket(InetAddress.getByName("localhost"), 9141);
			System.out.println("Connected to "
					+ clientSocket.getInetAddress().getHostName());
			
			/* step 2: connect input and output streams to the socket */
			ObjectInputStream oisFromServer = new ObjectInputStream(
					clientSocket.getInputStream());
			ObjectOutputStream oosToServer = new ObjectOutputStream(
					clientSocket.getOutputStream());
			System.out.println("I/O streams connected to the socket");

			/* step 3: communicate with the server */
			CreditCard c = new CreditCard(4012888888881881L);
			
			try {
				
				// send an object to the server
				oosToServer.writeObject(c);
				oosToServer.flush();
				System.out.println("\n### send this credit card number to the server for validation:\n" + c);

				// receive an object from the server
				c = (CreditCard) oisFromServer.readObject(); // casting!
				System.out.println("\n### the credit card returned by the server after validation:\n"+ c);
				
				try {
					
					Thread.sleep(5000);
					
				} catch (InterruptedException e) { }
				
			} catch (ClassNotFoundException cnf) {
				
				cnf.printStackTrace();
				
			} catch (EOFException eof) {
				
				System.out.println("The server has terminated connection!");
				
			} catch (IOException e) {
				
				e.printStackTrace();
				
			}
		
			 /* step 4: close the connection to the server */		
			System.out.println("\nClient: closing the connection...");
			oosToServer.close();
			oisFromServer.close();
			clientSocket.close();
			
		} catch (IOException ioe) {
			
			ioe.printStackTrace();
			
		}
		
		System.out.println("the client is going to stop runing...");
		
	}
}
