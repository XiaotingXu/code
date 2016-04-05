import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author  Xiaoting Xu
 * @version 1.0
 * @since   2016-03-28
 */

public class CreditCardServer {

	public static void main(String[] args) {
		
		ServerSocket serverSocket; // TCP socket used for listening

		try {
			/* step 1: create a server socket port number: 9141 */
			serverSocket = new ServerSocket(9141);

			/* setp 2: listen for a connection and create a socket */
			System.out.println("*** this server is going to validate the credit card ***");
			System.out.println("listening for a connection...");

			Socket socketConnection = serverSocket.accept();

			/* step 3: connect input and output streams to the socket */
			ObjectOutputStream oosToClient = new ObjectOutputStream(
					socketConnection.getOutputStream());

			ObjectInputStream oisFromClient = new ObjectInputStream(
					socketConnection.getInputStream());

			/* step 4: exchange objects with the client */
			CreditCard c;

			try {

				while (true) { // keep on getting data from the client

					// read an object from THE client
					c = (CreditCard) oisFromClient.readObject(); // casting!
					System.out.println("\n*** receive an credit card object from the CLIENT ***\n" + c);
					
					// validate the credit card
					c.setValid(CardValidation.isValid(c.getCreditCardNumber()));
			
					// send the object to THE client
					oosToClient.writeObject(c);
					oosToClient.flush();

					// display the result to the screen of the server
					System.out.println("\n*** send the validated credit card object to the CLIENT ***\n" + c);
					
				} // end while
			} catch (ClassNotFoundException cnf) {
				
				cnf.printStackTrace();
				
			} catch (EOFException eof) {
				
				System.out.println("\n*** the client has terminated connection ***");
				
			} catch (IOException e) {
				
				e.printStackTrace();
				
			}

			/* step 5: close the connection to the client */
			oosToClient.close();
			oisFromClient.close();
			socketConnection.close();
			
		} catch (IOException e) {
			
			e.printStackTrace();
			
		}
		
		System.out.println("\n*** the server is going to stop running ***");
		
	}

}
