package observador;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.client.LaxRedirectStrategy;
import org.apache.http.util.EntityUtils;

import com.google.api.client.googleapis.auth.oauth2.GoogleCredential;

class ServicoMovel
{
	private static final String ESCOPO = "https://www.googleapis.com/auth/firebase.messaging";	
	private static final String FCM_ENDPOINT = "https://fcm.googleapis.com/v1/projects/alarmsys-4c2f7/messages:send";

	private static List<String> tokens;

	static
	{
		tokens = new ArrayList<String>();
		tokens.add("fy95_jqnSzI:APA91bFAV8DsopeiTQ_u4CqnGCSCQOX6jY2X4Bdp8-wA9WA8MMwO0goeUcIjDnrQq23xNUJjTARHHVhZqnQqW6uBh5SRDThTR-GjfNrVD9AF9KGti3gx4DsxxH3WS3Bxr00rEKzfwVaL");
		// tokens.add("ciSdl51cfZ8:APA91bGo8xDbvHK20Ae8MAu4jkTDemtZqQlNcRVc_QbOP91ePINRdKcMt7VUUXw8jmto_qE_hDmKUydie_ShysHrUc2THgBnmC5mI4usI3G93i6T-LySo-j6z0IvG1XycOwUX5NvSJxx");
		// tokens.add("f38SFilWybI:APA91bE83U5Tfi-S-1EpoLlTn2QmHBGj8y9HZ9m3J--pmWKK_um9C7fafJmPFpej9_Mf6Pio4MlG32IQRjari7sL9kPnaOqIjfhLDoia2BGm0WLHYvrCEeCQA9A45q_YUkUMIbHb3PEi");
		// tokens.add("ceJCoEnUkx8:APA91bGaYIQdhqHoo0RcnlFdRMB_c0OPW4m9djGV5wp1VhNOAZGXsBALJxqlYAY5sYmfzP9NjxXEasyVgvbufUWDN1KkBbOP6yVdPbZqW1KterychM0MKhPx62NV55uD3D0LKh5mOUDS");
		// tokens.add("dTuDquICGYQ:APA91bGD1EJRaCTEPoy5rEs6U5Pwj_WZEU6bLWvVL48PFzJxuvluixww6FPdMCgOWi0aUB1_QRd0qlRlYzEiBNx1zWyK3iEn0TL_XfoTfkMuQG3UIaxDEzjMwOC-u7vzb-L18qc4JuFd");
	}

	private ServicoMovel()
	{
	}

	public static void enviarMensagem(String mensagem, Map<String, String> valores)
	{
		StringEntity stringJSON;
		HttpClient clienteHttp = HttpClientBuilder.create().setRedirectStrategy(new LaxRedirectStrategy()).build();
		
		try
		{
			for (String token : tokens)
			{
				HttpPost requisicaoHttp = new HttpPost(FCM_ENDPOINT);
				requisicaoHttp.addHeader("content-type", "application/json");
				requisicaoHttp.addHeader("Authorization", "Bearer " + getTokenAcesso());
				stringJSON = construirMensagemJSON(token, mensagem, valores);
				requisicaoHttp.setEntity(stringJSON);

				HttpResponse respostaHttp = clienteHttp.execute(requisicaoHttp); 
				HttpEntity respostaJSON = respostaHttp.getEntity();
				String respostaStr = EntityUtils.toString(respostaJSON);

				System.out.println(respostaStr);
			}
		}
		catch (UnsupportedEncodingException excecao)
		{
			System.out.println(excecao);
		}
		catch (IOException excecao)
		{
			System.out.println(excecao);
		}		
	}

	public static void receberMensagem(String token)
	{
	}

	private static StringEntity construirMensagemJSON(String token, String conteudo, Map<String, String> valores) throws UnsupportedEncodingException
	{
		// String stringJSON =	"{\r\n" + 
		// 	"\"message\":{\r\n" + 
		// 		"\"token\" : \"" + token + "\",\r\n" + 
		// 		"\"notification\" : { \r\n" + 
		// 			"\"title\" : \"SEAM Alerta!\",\r\n" + 
		// 			"\"body\" : \"" + conteudo + "\",\r\n" + 
		// 			"\"click_action\" : \"SEAM Alerta!\",\r\n" + 
		// 			"},\r\n" + 
		// 			"\"data\" : {\r\n";
		// 			int i = 0;
		// 			for (String chave : valores.keySet())
		// 			{
		// 				if (i < valores.size() - 1)
		// 					stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\",\r\n";
		// 				else
		// 					stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\"\r\n";
		// 				i++;
		// 			}
		// 		stringJSON += "} \r\n" + 
		// 		"} \r\n" +
		// 	"}";

		String stringJSON = "{\r\n" + 
				"\"message\":{\r\n" + 
					"\"token\" : \"" + token + "\",\r\n" + 
					"\"data\" : {\r\n";
						int i = 0;
						for (String chave : valores.keySet())
						{
							if (i < valores.size() - 1)
								stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\",\r\n";
							else
								stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\"\r\n";
							i++;
						}
					stringJSON += "} \r\n" + 
				"} \r\n" +
			"}";
		
		return (new StringEntity(stringJSON));
	}

	private static String getTokenAcesso() throws IOException
	{
		GoogleCredential credencialGoogle = GoogleCredential.fromStream(new FileInputStream("observador/recursos/alarmsys-4c2f7-firebase-adminsdk-hp4xq-375c23ca94.json")).createScoped(Arrays.asList(ESCOPO));
		credencialGoogle.refreshToken();

		return (credencialGoogle.getAccessToken());
	}
}