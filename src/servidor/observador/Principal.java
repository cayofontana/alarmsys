class Principal
{
	public static void main(String[] args)
	{
		Observador observador = new Observador();

		while (true)
			try
			{
				if (observador.estadoMudou())
					ServicoMovel.enviarMensagem(observador.getDeteccaoReferencia().imprimir());

				Thread.sleep(10000);
			}
			catch (InterruptedException excecao)
			{
				System.out.println(excecao);
			}
	}
}