package imp.modelo;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Date;

import imp.infraestrutura.Util;
import imp.modelo.persistencia.AcessoDados;

public class Deteccao
{
	private int id;
	private float valor;
	private Date data;

	private AcessoDados acessoDados;

	public Deteccao(AcessoDados acessoDados)
	{
		this.acessoDados = acessoDados;
	}

	public Deteccao()
	{
		id = 0;
		valor = 0.0F;
		data = null;
	}

	public int getId()
	{
		return (id);
	}

	public String obterInformacoes()
	{
		String strInfo;

		strInfo = "id: " + id + "\n";
		strInfo += "valor: " + valor + "\n";
		strInfo += "datahora: " + Util.obterTexto(data);

		return (strInfo);
	}

	public Map<String, String> obterValores()
	{
		Map<String, String> valores = new HashMap<String, String>();

		valores.put("id", Integer.toString(id));
		valores.put("valor", Float.toString(valor));
		valores.put("datahora", Util.obterTexto(data));

		return (valores);
	}

	public void preencherUltima()
	{
		List<String> objetos;
		String sqlConsulta;
		int i = 0;

		sqlConsulta = "SELECT ";
		sqlConsulta += "DETE_ID_DETECCAO, ";
		sqlConsulta += "DETE_VL_DISTANCIA_MEDIA, ";
		sqlConsulta += "DETE_DT_DETECCAO ";
		sqlConsulta += "FROM DETECCAO ";
		sqlConsulta += "ORDER BY DETE_ID_DETECCAO ";
		sqlConsulta += "DESC LIMIT 1";

		objetos = acessoDados.listar(sqlConsulta);

		if (objetos != null && !objetos.isEmpty())
		{
			id = Integer.parseInt(objetos.get(i++));
			valor = Float.parseFloat(objetos.get(i++));
			data = Util.construirData(objetos.get(i++));
		}
	}
}
