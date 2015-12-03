using UnityEngine;
using System.Collections;
using System.Reflection;
using System;
using System.IO;
using System.Collections.Generic;

public class ExportableAttribute : Attribute
{
    public ExportableAttribute() { }
}


public class ExportableManager : MonoBehaviour {

    private List<string> toExport;
    private List<List<string>> allObjects;

	// Use this for initialization
	public void export () {
        StreamWriter sw = File.CreateText("pruebaMap.txt");
        allObjects = new List<List<string>>(100);
        toExport = new List<string>(1);
        toExport.Add("Map = {	");
        allObjects.Add(toExport);
        //sw.WriteLine("Map = {	");
        GameObject[] objects = GameObject.FindObjectsOfType<GameObject>();
        
        for (int j = 0; j < objects.Length; ++j)
        {
            processObject(objects[j]);
            writeObject(objects[j], sw);
        } // for (int j = 0; j < objects.Length; ++j)


        toExport = new List<string>(1);
        toExport.Add("}");
        allObjects.Add(toExport);
        //sw.WriteLine("}");

        for (int i = 0; i < allObjects.Count; ++i)
        {
            List<string> aux = allObjects[i];
            bool entity = false;
            bool model = false;
            if (i == 0 || i == allObjects.Count-1)//una chapuza mas, el primero y el utlimo pasan siempre
            {
                entity = true;
                model = true;
            }
            for (int j = 0; j < aux.Count; ++j)
            {
                if (aux[j].Contains("Entity"))
                {
                    entity = true;
                }
                if (aux[j].Contains("model"))
                {
                    model = true;
                }
            }
            if (entity && model)
            {
                for (int j = 0; j < aux.Count; ++j)
                {
                    sw.WriteLine(aux[j]);
                }
            }
        }

        sw.Close();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    private bool existName(string name)
    {
        for (int i = 0; i < allObjects.Count;++i )
        {
            List<string> aux = allObjects[i];
            if (aux[0].Equals("\t" + name + " = {	"))
                return true;
        }

        return false;
    }
    private void writeObject(GameObject gameObject, StreamWriter sw)
    {
        if (toExport.Count > 4)
        {
            MeshFilter aux = gameObject.GetComponent<MeshFilter>();
            if (aux != null)
            {
                if (aux.mesh.name.Contains("Combined"))
                {
                    int isdfs = 0;
                }
                else
                {
                    toExport.Add("\t\tmodel = \"" + aux.mesh.name.Substring(0, aux.mesh.name.LastIndexOf("Instance") - 1) + ".mesh\",");
                }
            }
            BoxCollider boxCollider = gameObject.GetComponent<BoxCollider>();
            if (boxCollider != null)
            {
                //TODO: de alguna forma hay que ponerle la ruta completa
                toExport.Add("\t\tcolliderSize = " + boxCollider.size + ",");
                toExport.Add("\t\tcolliderCenter = " + boxCollider.center + ",");
                toExport.Add("\t\tisTrigger = " + boxCollider.isTrigger.ToString().ToLower()+",");
            }
            SphereCollider sphereCollider = gameObject.GetComponent<SphereCollider>();
            if (sphereCollider != null)
            {
                //TODO: de alguna forma hay que ponerle la ruta completa
                toExport.Add("\t\tcolliderRadius = " + sphereCollider.radius + ",");
                toExport.Add("\t\tcolliderCenter = " + sphereCollider.center + ",");
                toExport.Add("\t\tisTrigger = " + sphereCollider.isTrigger.ToString().ToLower() + ",");
            }

            toExport.Add("\t},");
            for (int w = 0; w < toExport.Count; ++w)
            {
                toExport[w] = toExport[w].Replace('(', '{');
                toExport[w] = toExport[w].Replace(')', '}');

                //toExport[w] = toExport[w].Replace('?', '(');
                //toExport[w] = toExport[w].Replace('¿', ')');

                //sw.WriteLine(toExport[w]);
            } //for (int w = 0; w < toExport.Count; ++w)
            allObjects.Add(toExport);
        } //if (toExport.Count > 1)
    }
    static int repetidos = 0;
    private void processObject(GameObject gameObject)
    {
        toExport = new List<string>();
        string name = gameObject.name;
        if (name.IndexOf('(') > -1)
        {
            name = name.Remove(name.IndexOf('('), 1);
        }
        if (name.IndexOf(')') > -1)
        {
            name = name.Remove(name.IndexOf(')'), 1);
        }
        name = name.Replace(' ', '_');
        name = name.Trim();// (new Char[] { ' ' });
        
        while (existName(name))
        {
            ++repetidos;
            name += repetidos;
        }
        toExport.Add("\t" + name + " = {	");

        Component[] components = gameObject.GetComponents<Component>();
        for (int z = 0; z < components.Length; ++z)
        {
            processComponent(components[z]);
        }

        toExport.Add("\t\tposition = " + gameObject.transform.position + ",");
        toExport.Add("\t\tscale = " + gameObject.transform.localScale + ",");
        toExport.Add("\t\trotation = " + gameObject.transform.rotation.eulerAngles + ",");
    }
    private void processComponent(Component component)
    {
        FieldInfo[] objectFields = component.GetType().GetFields(BindingFlags.Instance | BindingFlags.Public);

        for (int i = 0; i < objectFields.Length; ++i)
        {
            processField(objectFields[i], component);
        } //for (int i = 0; i < objectFields.Length; ++i)
    }
    private void processField(FieldInfo fielInfo, Component component)
    {
        ExportableAttribute attribute = Attribute.GetCustomAttribute(fielInfo, typeof(ExportableAttribute)) as ExportableAttribute;
        if (attribute != null)
        {
            processAttribute(fielInfo, component);
        } // if (attribute != null)
    }
    private void processAttribute( FieldInfo fielInfo, Component component)
    {
        if (fielInfo.FieldType == typeof(System.String))
        {
            toExport.Add("\t\t" + fielInfo.Name + " = \"" + fielInfo.GetValue(component) + "\",");
        }
        else
        {
            toExport.Add("\t\t" + fielInfo.Name + " = " + fielInfo.GetValue(component) + ",");
        }
    }
}
