package barbeirosdorminhocos;

public class Cliente extends Pessoa{
	
	private Barbeiro barbeiro;
	
	public Cliente (int id) {
		super(id);
	}
	
	public void run (int barbeirosAtendendo, int quantBarbeiros, long[]fila) {
		
		
		
	}
	
	public void setBarbeiro (Barbeiro b) {
		this.barbeiro = b;
	}
	public Barbeiro getBarbeiro () {
		return barbeiro;
	}
	

}
