package imp;

import imp.modelo.Observador;
import imp.modelo.Token;
import imp.modelo.persistencia.AcessoDados;
import imp.servico.ServicoMovel;

class Principal
{
	public static void main(String[] args)
	{
		AcessoDados acessoDados = new AcessoDados();
		Observador observador = new Observador(acessoDados);
		Token token = new Token(acessoDados);

		while (true)
			try
			{
				if (observador.estadoMudou(acessoDados))
					ServicoMovel.enviarMensagem(token.listar(), observador.getDeteccaoReferencia().obterInformacoes(), observador.getDeteccaoReferencia().obterValores());

				Thread.sleep(5000);
			}
			catch (InterruptedException excecao)
			{
				System.out.println(excecao);
			}
	}
}