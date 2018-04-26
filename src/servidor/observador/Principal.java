class Principal
{
	public static void enviarMensagem(String mensagem)
	{
		// IMPLEMENTAR AQUI O CÓDIGO QUE NOTIFICA OS TELEFONES
		System.out.println(mensagem);
	}

	public static void main(String[] args)
	{
		Observador observador = new Observador();

		while (true)
			try
			{
				if (observador.estadoMudou())
					enviarMensagem(observador.getDeteccaoReferencia().imprimir());

				Thread.sleep(10000);
			}
			catch (InterruptedException excecao)
			{
				System.out.println(excecao);
			}
	}
}