using UnityEngine;
using System.Collections;

/// <summary>
/// Creates an indicator for the life
/// </summary>
[RequireComponent(typeof(Life))]
public class LifeFeedback : MonoBehaviour {

    private Life m_life; // The life script attach to this gameObject
    private float m_maxLife; // The maximum life of this gameObject

    public GameObject m_lifeIndicatorPrefab; // The lifeIndicator prefab
    private GameObject m_lifeSprite; // The sprite indicator
    private float m_initScale;

    void Awake()
    {
        m_life = GetComponent<Life>();
        m_maxLife = m_life.getMaxLife();
    }

    public bool OnDamage(float damage){

        instanciateLifeSprite();

        // Calculates the life percentage
        float lifePercent = m_life.getLife() / m_maxLife;

        // Scales the sprite by the lifePercent
        Vector3 spriteScale = m_lifeSprite.gameObject.transform.localScale;
        spriteScale.x *= lifePercent;
        m_lifeSprite.gameObject.transform.localScale = spriteScale;

        return true;
    }

    private void instanciateLifeSprite()
    {
        if (m_lifeSprite == null)
        {
            m_lifeSprite = Instantiate<GameObject>(m_lifeIndicatorPrefab); // Instantiate the life sprite
            m_lifeSprite.transform.parent = transform; // Set it a children of this gameObject
            m_lifeSprite.transform.localPosition = m_lifeIndicatorPrefab.transform.localPosition; // Resets its position
            m_lifeSprite.transform.localRotation = m_lifeIndicatorPrefab.transform.localRotation; // Resets its rotation
            m_lifeSprite.transform.localScale = m_lifeIndicatorPrefab.transform.localScale; // Resets its scale

            // Give values to some variables
            m_initScale = m_lifeSprite.gameObject.transform.localScale.x;
        }
    }
}
