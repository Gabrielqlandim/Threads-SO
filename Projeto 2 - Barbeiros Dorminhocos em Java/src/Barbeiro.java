public class Barbeiro extends Pessoa{
    public void run() {

    Barbearia barbearia = new Barbearia();

    Cliente cliente = barbearia.proximoCliente();
    barbearia.corteTerminado(cliente);


    }
}
