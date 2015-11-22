using UnityEngine;
using System.Collections;

public class ExplosiveObject : MonoBehaviour {

    public GameObject m_explosionParticle;
    public GameObject m_flareParticle;
    public Transform m_flarePoint;

    private Object flareInstance = null;

    void Update () {
        //si tiene menos de 2/3 de vida, saltan chispas
        if(gameObject.GetComponent<Life>().getLife() <= gameObject.GetComponent<Life>().getMaxLife()*2/3)
        {
            if(flareInstance == null)
            {
                flareInstance = Instantiate(m_flareParticle, m_flarePoint.position, transform.rotation);
            }
        }
        else //si recupera la vida, vuelve al estado normal
        {
            if (flareInstance != null)
            {
                Destroy(flareInstance);
                flareInstance = null;
            }
        }

    }

    public void OnDead()
    {
        Debug.Log("HE EXPLOTADO; HIJOS DE LA CHINGADA!");
        //poner la animación y sonido de explosión
        Instantiate(m_explosionParticle, transform.position, transform.rotation);

        //destruye el objeto
        Destroy(gameObject);

        //destruye el objeto padre de la jerarquía
        GameObject parent = gameObject.transform.parent.gameObject;
        Destroy(parent);
    }
}
