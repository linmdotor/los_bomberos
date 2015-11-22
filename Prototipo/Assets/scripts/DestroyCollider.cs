using UnityEngine;
using System.Collections;

/**
 * Este componente se pone a los objetos que queremos que desaparezcan al colisionar con el "Player" 
 * Para que funcione, el GameObject debe tener un Collider, con el "isTrigger" activado.
 */
public class DestroyCollider : MonoBehaviour
{
    public string m_Tag = "Entrance";
    //public float m_damage = 10.0f;
    public bool m_destroyOnCollision = true;

    public void OnTriggerEnter(Collider other)
    {
        if (other.transform.CompareTag(m_Tag))
        {
            //other.gameObject.SendMessage("damage", m_damage, SendMessageOptions.DontRequireReceiver);
            if (m_destroyOnCollision)
                Destroy(gameObject);
        }
    }
}