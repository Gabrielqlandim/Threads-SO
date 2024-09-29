package barbeirosdorminhocos;

import java.util.Scanner;
import java.util.concurrent.LinkedBlockingQueue;

public class Main {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		
		int tamanhoFila, quantClientes, quantBarbeiros, barbeirosAtendendo = 0, clientesEsperando = 0;
		
		tamanhoFila = scan.nextInt();
		quantBarbeiros = scan.nextInt();
		quantClientes = scan.nextInt();
		
		Barbeiro[] barbeiros = new Barbeiro[quantBarbeiros];
		Cliente[] clientes = new Cliente[quantClientes];
		
		for (int i=0; i<quantBarbeiros; i++) {
			barbeiros[i] = new Barbeiro(i+1);
			barbeiros[i].start();
		}
		
		for (int i=0; i<quantClientes; i++) {
			clientes[i] = new Cliente(i+1);
			clientes[i].start();
			
		}
		
		Barbearia barbearia = new Barbearia(quantBarbeiros, tamanhoFila);
		int c = 0;
		
		while(true) {
			if (barbearia.cortaCabelo(clientes[c])) {
				barbearia.corteTerminado(barbearia.proximoCliente());
			}
			
			c++;
			
			if (c == quantClientes) {
				break;
			}
		}
		
		
		System.out.println("OI");

	}

}
