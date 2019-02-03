class Principal
{
	public static void main(String[] args)
	{
		Observador observador = new Observador();

		while (true)
			try
			{
				if (observador.estadoMudou())
					ServicoMovel.enviarMensagem(observador.getDeteccaoReferencia().imprimir(), observador.getDeteccaoReferencia().obterValores());

				Thread.sleep(5000);
			}
			catch (InterruptedException excecao)
			{
				System.out.println(excecao);
			}
	}
}