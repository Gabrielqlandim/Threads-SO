package barbeirosdorminhocos;

import java.util.concurrent.LinkedBlockingQueue;

public class Barbearia {
	
	private int barbeirosAtendendo = 0;
	private int quantBarbeiros;
	private int tamanhoFila;
	private Barbeiro[] barbeiros;
	
	LinkedBlockingQueue<Cliente> fila = new LinkedBlockingQueue<>(tamanhoFila);
	
	public Barbearia (int quantBarbeiros, int tamanhoFila) {
		this.quantBarbeiros = quantBarbeiros;
		this.tamanhoFila = tamanhoFila;
		this.barbeiros = new Barbeiro[quantBarbeiros];
	}
	
	public boolean cortaCabelo (Cliente c) {
		
		if (barbeirosAtendendo < quantBarbeiros) {
			return true;
		}
		else {
			return false;
		}
			
	}
	
	public Cliente proximoCliente () {
		
		Cliente c;
		
		for (Barbeiro b: barbeiros) {
			if (b.isDisponivel()) {
				c = (fila.peek());
				c.setBarbeiro(b);
				break;
			}
		}
		
		System.out.println("Cliente " + c.getId() + " cortando cabelo com Barbeiro " + c.getBarbeiro().getId());
		barbeirosAtendendo++;
		
		return fila.poll();
	}
	
	public void corteTerminado (Cliente c) {
		c.setBarbeiro(null);
		barbeirosAtendendo--;
	}
}
