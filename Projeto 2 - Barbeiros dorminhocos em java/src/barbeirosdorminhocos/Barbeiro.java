package barbeirosdorminhocos;

public class Barbeiro extends Pessoa{
	
	private boolean disponivel = true;
	
	public Barbeiro (int id) {
		super(id);
	}
	
	public void run () {
		
	}
	
	public boolean isDisponivel() {
		return disponivel;
	}
	
	public void setDisponivel(boolean disponivel) {
		this.disponivel = disponivel;
		
	}

}
